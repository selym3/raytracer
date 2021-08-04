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

public:
    Camera camera;
    std::vector<Collider> colliders;

    sf::Color getColor(const sf::Vector2<std::size_t>& pixel) const
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
            return sf::Color(int(n.x), int(n.y), int(n.z));
        }

        // If there isn't, background color
        auto dy = ray.direction.y;
        Vec3d c1 = Vec3d(128, 128, 128),
              c2 = Vec3d(59, 59, 59);

        // std::cout << ray.direction.y << "\n";

        auto c_mix = c1 * (1 - dy) + c2 * dy;

        return sf::Color(int(c_mix.x), int(c_mix.y), int(c_mix.z));

    }

private:

    void updatePixels()
    {
        sf::Vector2<std::size_t> pixel(0, 0);
        for (; pixel.y < buffer.get_height(); ++pixel.y)
        {
            for (pixel.x = 0; pixel.x < buffer.get_width(); ++pixel.x)
            {
                buffer.set_color(pixel, getColor(pixel));
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

    Engine(std::size_t width, std::size_t height) :
        window(
            sf::VideoMode(width, height),
            "raytracer",
            sf::Style::None
        ),
        buffer(window.getSize()),
        camera(width, height, 90.0)
    {
        colliders.push_back(SphereCollider({0,0,+6}, 2));
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