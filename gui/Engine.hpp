#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

#include <cstdlib>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Pixels.hpp"
#include "../tracing/Shape.hpp"
#include "../tracing/Camera.hpp"

class Engine
{
private:
    sf::RenderWindow window;
    Pixels buffer;
    int samples_per_pixel;

public:
    Camera camera;
    std::vector<Collider> colliders;

    template <typename V3>
    static sf::Color toColor(const V3& v)
    {
        return sf::Color(
            static_cast<sf::Uint8>(v.x),
            static_cast<sf::Uint8>(v.y),
            static_cast<sf::Uint8>(v.z)
        );
    }

    template <typename Pixel>
    Vec3d getColor(const Pixel& pixel) const
    {   
        // Camera ray
        auto ray = camera.get_ray(pixel);

        // Test against every shape in the scene
        CollisionTest nearest = std::nullopt;
        for (const auto& collider : colliders)
        {
            auto collision = collider(ray);
            if (collision.has_value())
            {
                if (nearest.has_value())
                    nearest = (collision.value() < nearest.value()) ? 
                        collision : 
                        nearest;

                else
                    nearest = collision;

            }
        }

        // If there is a shape in the scene,
        if (nearest.has_value())
        {
            auto n = nearest->normal;
            n+=1; n *= 0.5;
            n*=255;
            return n;
        }

        // If there isn't, background color
        auto dy = ray.direction.y;
        Vec3d c1 = Vec3d(128, 128, 128),
              c2 = Vec3d(59, 59, 59);

        auto c_mix = c1 * (1 - dy) + c2 * dy;

        return c_mix;
    }

private:

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

    Engine(std::size_t width, std::size_t height, int samples_per_pixel = 1) :
        window(
            sf::VideoMode(width, height),
            "raytracer",
            sf::Style::None
        ),
        buffer(window.getSize()),
        camera(width, height, 90.0),
        samples_per_pixel(samples_per_pixel)
    {
        colliders.push_back(SphereCollider({-3, 0, 6}, 2));
        colliders.push_back(SphereCollider({+3, 0, 6}, 2));
        colliders.push_back(PlaneCollider({0,-8,0}, {0,1,0}));
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