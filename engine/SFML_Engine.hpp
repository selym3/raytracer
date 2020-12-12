#ifndef __SFML_ENGINE_HPP__
#define __SFML_ENGINE_HPP__

#include "./Engine.hpp"
#include <SFML/Graphics.hpp>

struct SFML_Engine : public Engine 
{

    SFML_Engine(int width, int height);
    ~SFML_Engine()=default;

    bool isRunning() const override;
    void execute() override;

private:

    sf::RenderWindow window;

};

#endif