#include "../../engine/SFML_Engine.hpp"

#include <cmath>
#include <thread>

SFML_Engine::SFML_Engine(int w, int h, Camera camera, Light light, int rowsPerThread) : 
    Engine(
        w, 
        h, 
        light,
        camera
    ),
    window(
        sf::VideoMode(w, h),
        "Raytracer Engine",
        sf::Style::None
    ),
    rowsPerThread { rowsPerThread }
{
}

SFML_Engine::SFML_Engine(int w, int h, Camera camera, Light light) :
    SFML_Engine(w, h, camera, light, w)
{
}

bool SFML_Engine::isRunning() const
{
    return window.isOpen();
}

#include <iostream>

void SFML_Engine::execute() 
{

    // TODO: add a timer

    sf::Event event;
    while (window.pollEvent(event)) 
    {
    
        if (event.type == sf::Event::Closed)
            window.close();

    }

    auto getKey = [](sf::Keyboard::Key a) {
        return sf::Keyboard::isKeyPressed(a);
    };

    if (getKey(sf::Keyboard::Escape))
        window.close();

    if (getKey(sf::Keyboard::Space)) {
        std::cout << camera.translation.x << ", " << camera.translation.y << ", " << camera.translation.z << "\n";
        std::cout << camera.yaw << ", " << camera.pitch << ", " << camera.roll << "\n";
        std::cout << "---\n";
    }

    // camera movement 
    // auto isMoving = (getKey(sf::Keyboard::W) - getKey(sf::Keyboard::S));
    Vec3 dir { 0, 0, 0.2 * (getKey(sf::Keyboard::W) - getKey(sf::Keyboard::S)) };
    camera.translation += dir.rotate(camera.yaw, camera.pitch, camera.roll);
    camera.translation.y += 0.2 * (getKey(sf::Keyboard::Q) - getKey(sf::Keyboard::E));


    // rotating
    camera.pitch += 0.9 * (getKey(sf::Keyboard::A) - getKey(sf::Keyboard::D));

    window.clear(sf::Color::White);

    std::vector<sf::Vertex> vertexArray;
    vertexArray.resize(height * width);

    std::vector<std::thread> pool;

    auto worker = [&](int first, int second) {
        for (int row = first; row < second; ++row) {
            for (int i = 0; i < width; ++i) {

                auto ray = this->camera.project(i, row);
                auto color = this->trace(ray);

                vertexArray[row * width + i] = sf::Vertex(
                    sf::Vector2f(i, row),
                    sf::Color(
                        color.x * 255,
                        color.y * 255,
                        color.z * 255
                    )
                );
            }
        }
    };

    for (
        int first = height - rowsPerThread, second = height;
        second > 0;
        first -= rowsPerThread, second -= rowsPerThread
    ) {
        pool.push_back(std::thread(
            worker,
            (first > 0 ? first : 0),
            second
        ));
    }

    for (auto& thread : pool)
        thread.join();
    
    window.draw(&vertexArray[0], vertexArray.size(), sf::Points);

    window.display();

}