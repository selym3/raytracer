#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

#include <SFML/Graphics.hpp>
#include <cstdlib>

#include "Pixels.hpp"

class Engine
{
    sf::RenderWindow window;
    Pixels buffer;

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

private:

    void draw()
    {
        window.clear(sf::Color::White);

        sf::Vector2<std::size_t> pixel(0, 0);
        for (; pixel.y < buffer.get_height(); ++pixel.y) 
        {
            for (pixel.x = 0; pixel.x < buffer.get_width(); ++pixel.x)
            {
                auto r = rand() % 256;
                buffer.set_color(pixel, sf::Color(r, r, r));
            }
        }

        window.draw(buffer);
        window.display();
    }

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
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            handleEvent(event);    
        }

        draw();
    }


};

#endif