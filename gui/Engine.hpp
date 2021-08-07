#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

#include <cstdlib>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Pixels.hpp"
#include "../tracing/Shape.hpp"
#include "../tracing/Camera.hpp"


/////////////
// https://stackoverflow.com/questions/2704521/generate-random-double-numbers-in-c
#include <random>
template<typename Numeric, typename Generator = std::mt19937>
Numeric random(Numeric from, Numeric to)
{
    thread_local static Generator gen(std::random_device{}());

    using dist_type = typename std::conditional
    <
        std::is_integral<Numeric>::value
        , std::uniform_int_distribution<Numeric>
        , std::uniform_real_distribution<Numeric>
    >::type;

    thread_local static dist_type dist;

    return dist(gen, typename dist_type::param_type{from, to});
}
/////////////

Vec3d random_in_sphere()
{
    // angles
    double xy = random(-180.0, +180.0),
           yz = random(-180.0, +180.0);
    
    // Rotations & Scaling
    double x = random(0,1) * std::cos(yz) * std::sin(xy);
    double y = random(0,1) * std::cos(yz) * std::cos(xy);
    double z = random(0,1) * std::sin(yz);
    
    return Vec3d(x, y, z);
}


/////////////


class Engine
{
private:
    sf::RenderWindow window;
    Pixels buffer;
    int samples_per_pixel;

public:
    Camera camera;
    std::vector<Shape> shapes;

    double fuzz = 0.0;
    int max_depth = 3;

    // struct Light
    // {
    //     Vec3d position, color;

    //     Light(const Vec3d& position, const Vec3d& color) :
    //         position{position}, color{color}
    //     {
    //     }
    // };

    // std::vector<Light> lights;


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

    Vec3d getBackgroundColor(const Ray& ray) const
    {
        // Simple gradient to look nice
        auto dy = ray.direction.y;
        Vec3d c1 = Vec3d(0, 0, 144),
              c2 = Vec3d(255, 255, 255);

        auto c_mix = c1 * (1 - dy) + c2 * dy;

        return c_mix;
    }

    Vec3d getSurfaceColor(const Surface& surface) const
    {
        const Vec3d& normal = surface.collision.normal,
            where = surface.collision.where;

        Vec3d result = surface.color;
        // for (const Light& light : lights)
        // {
        //     Ray light_ray = Ray(where, light.position - where).fix(normal, 0.01);
        //     bool sees_light = !hitsSurface(light_ray);

        //     if (sees_light)
        //         result += light.color;
        // }
        return result;
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
            const Vec3d& normal = surface->collision.normal,
                where = surface->collision.where;

            Vec3d result = surface->color;

            Ray reflected = ray.reflect(where, normal, 0.01);
            reflected.direction += fuzz * random_in_sphere();
            reflected.direction = !reflected.direction;

            return result + 0.5 * raytrace(reflected, depth-1);
        }

        // If not, compute background color
        else return getBackgroundColor(ray);
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
        double z = 4;
        double r = 1;
        double s = 0.1;

        // lights.push_back(Light({0, r*3, z}, Vec3d{249, 252, 71}/3.0));

        shapes.push_back(Shape(SphereCollider({-(r + s), 0, z}, r), {64, 0, 0}));
        shapes.push_back(Shape(SphereCollider({+(r + s), 0, z}, r), {0, 0, 64}));
        shapes.push_back(Shape(PlaneCollider({0, -(r + s),0}, {0,1,0}), {0, 64, 0}));
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