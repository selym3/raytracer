#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

#include <cstdlib>
#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "Pixels.hpp"
#include "../tracing/Shape.hpp"
#include "../tracing/Camera.hpp"

class Engine
{
private:
    sf::RenderWindow window;
    Pixels buffer;

public:
    Camera camera;
    std::vector<Shape> shapes;
    LightSet lights;

    Vec3d bg_color;

    int samples_per_pixel;
    int max_depth = 6;

    std::optional<Surface> getSurface(const Ray& ray, bool any = false) const
    {
        std::optional<Surface> nearest = std::nullopt;
        for (const auto& shape : shapes)
        {
            std::optional<Surface> surface = shape.intersect(ray);
            if (surface.has_value())
            {
                if (any) 
                    return surface;

                if (nearest.has_value())
                    nearest = (surface->collision < nearest->collision) ? 
                        surface : 
                        nearest;

                else
                    nearest = surface;

            }
        }

        return nearest;
    }

    bool hitsSurface(const Ray& ray) const
    {
        return getSurface(ray, true).has_value(); 
    }


    Vec3d raytrace(const Ray& ray, int depth) const
    {
        // If the ray can't bounce anymore, quit
        if (0 >= depth) return Vec3d(0,0,0);

        // Calculate where ray intersects scene
        auto surface = getSurface(ray);

        // If ray intersected a surface, continue ray tracing
        if (surface.has_value())
        {
            auto surface_color = surface->getSurfaceColor(ray, lights);
            
            for (const Ray& ray : surface_color.rays)
                surface_color.color += (surface_color.absorption * raytrace(ray, depth - 1));
            
            return surface_color.color;
        }

        // If not, compute background color
        else return bg_color;
    }

private:

    template <typename V3>
    static sf::Color toColor(const V3& v)
    {
        return sf::Color(
            static_cast<sf::Uint8>(v.x),
            static_cast<sf::Uint8>(v.y),
            static_cast<sf::Uint8>(v.z)
        );
    }

    template <typename V3>
    Vec3d getColor(const V3& pixel) const
    {   
        // Primary camera ray
        auto ray = camera.get_ray(pixel);
        return raytrace(ray, max_depth);
    }

    void updatePixels()
    {
        auto pixel_increment = 1.0 / static_cast<double>(samples_per_pixel);
        sf::Vector2<double> pixel(0, 0);
        
        for (; pixel.y < buffer.get_height(); ++pixel.y)
        {
            for (pixel.x = 0; pixel.x < buffer.get_width(); ++pixel.x)
            {
                auto exact_x = pixel.x;
                Vec3d color = 0;
                for (int sample = 0; sample < samples_per_pixel; ++sample)
                {
                    color += getColor(pixel);
                    pixel.x += pixel_increment;
                }
                pixel.x = exact_x;
                
                buffer.set_color(pixel, toColor(color/samples_per_pixel));
            }
        }
    }

    void draw()
    {
        window.clear(sf::Color::White);

        updatePixels();

        window.draw(buffer);
        window.display();
    }

private:

    void handleEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }

            
        }
    }


public:

    Engine(
        std::size_t width, std::size_t height, 
        const Camera& camera, const Vec3d& bg_color, 
        const std::vector<Shape>& shapes, const LightSet& lights, 
        int max_depth, int samples_per_pixel
    ) :
        window(
            sf::VideoMode(width, height),
            "raytracer",
            sf::Style::None
        ),
        buffer(window.getSize()),
        camera(camera),
        shapes(shapes),
        lights(lights),
        max_depth(max_depth),
        samples_per_pixel(samples_per_pixel),
        bg_color(bg_color)
    {
    }

    bool is_running() const 
    {
        return window.isOpen();
    }

    void update()
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            handleEvent(event);    
        }

        draw();
    }


};

#endif