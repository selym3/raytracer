#include "./engine/PPM_Engine.hpp"
#include "./raytracing/Sphere.hpp"
#include <iostream>
int main(void)
{
    constexpr int WIDTH  = 300;
    constexpr int HEIGHT = 300;

    using EngineType = PPM_Engine;

    EngineType engine{
        WIDTH,
        HEIGHT
    };

    engine
        .addShape(Sphere(Vec3( 0, -2.5, -30), 4, Color(1, 0, 0)))
        .addShape(Sphere(Vec3( 0, 0, -60), 12, Color(0, 1, 0)));

    std::cout << "Start rendering..." << std::endl;

    while (engine.isRunning()) {
        engine.execute();
    }

    std::cout << "Done rendering..." << std::endl;

    return 0;
}