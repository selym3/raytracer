#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

#include <SFML/Graphics.hpp>
#include "Pixels.hpp"

// #include <crandom>

class Engine
{
    sf::RenderWindow window;
    Pixels buffer;

public:
    Engine(std::size_t width, std::size_t height) :
        window(
            sf::VideoMode(width, height),
            "raytracer",
            sf::Style::None
        ),
        buffer(
            window.getSize()
        )
    {
    }

    bool is_running() const 
    {
        return window.isOpen();
    }

    void update()
    {
        sf::Vector2<std::size_t> pixel(0, 0);
        for (; pixel.y < buffer.get_height(); ++pixel.y) 
        {
            for (pixel.x = 0; pixel.x < buffer.get_width(); ++pixel.x)
            {
                // auto r = 
            }
        }
    }


};

#endif