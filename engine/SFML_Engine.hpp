#ifndef __SFML_ENGINE_HPP__
#define __SFML_ENGINE_HPP__

#include "./Engine.hpp"
#include "./projections/Camera.hpp"
#include <SFML/Graphics.hpp>

struct SFML_Engine : public Engine 
{

    SFML_Engine(int width, int height, Camera projector);
    SFML_Engine(int width, int height, Camera projector, int rowsPerThread);
    ~SFML_Engine()=default;

    bool isRunning() const override;
    void execute() override;

private:

    int rowsPerThread;
    sf::RenderWindow window;

};

#endif