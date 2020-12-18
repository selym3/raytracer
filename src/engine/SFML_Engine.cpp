#include "../../engine/SFML_Engine.hpp"

SFML_Engine::SFML_Engine(int w, int h, Camera camera) : 
    Engine(
        w, 
        h, 
        Engine::Light(w>>1, 300, -5),
        camera
    ),
    window(
        sf::VideoMode(w, h),
        "Raytracer Engine",
        sf::Style::None
    )
{
}

bool SFML_Engine::isRunning() const
{
    return window.isOpen();
}

void SFML_Engine::execute() 
{

    sf::Event event;
    while (window.pollEvent(event)) 
    {
    
        if (event.type == sf::Event::Closed)
            window.close();

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();

    window.clear(sf::Color::White);

    std::vector<sf::Vertex> vertexArray;
    vertexArray.resize(height * width);

    sf::Vertex pixel(
        sf::Vector2f(0,0),
        sf::Color::Black
    );

    // std::cout << width << ", " << height << "\n";
    for (int y = 0; y < height; ++y) {

        for (int x = 0; x < width; ++x) {
        
            auto primaryRay = this->camera.project(x, y);

            auto color = this->trace(primaryRay);

            // whack
            pixel.position.x = x;
            pixel.position.y = y;
            pixel.color.r = sf::Uint8(color.x * 255);
            pixel.color.g = sf::Uint8(color.y * 255);
            pixel.color.b = sf::Uint8(color.z * 255);

            vertexArray.push_back(pixel);

        }

    }

    window.draw(&vertexArray[0], vertexArray.size(), sf::Points);

    window.display();

}