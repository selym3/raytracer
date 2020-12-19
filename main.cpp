#include "./engine/projections/Camera.hpp"
#include "./engine/projections/Orthographic.hpp"
#include "./engine/projections/Perspective.hpp"
#include "./engine/projections/Projection.hpp"

#include "./engine/PPM_Engine.hpp"
#include "./engine/SFML_Engine.hpp"
#include "./raytracing/Sphere.hpp"

#include <iostream>


int main(void)
{
    // -lsfml-window -lsfml-graphics -lsfml-system -pthread

    constexpr int WIDTH  = 900;
    constexpr int HEIGHT = 450;

    // using EngineType = PPM_Engine;
    using EngineType = SFML_Engine;

    EngineType engine {
        WIDTH,
        HEIGHT,
        Camera(
            Perspective(
                90, 
                WIDTH, 
                HEIGHT
            )
        ),
        1
    };

    engine
        .addShape(Sphere(Vec3( 0, -2.5, -30), 4, Color(1, 0, 0)))
        .addShape(Sphere(Vec3( 0, 0, -60), 12, Color(0, 1, 0)));

    std::cout << "Start rendering...\n";

    while (engine.isRunning()) {
        engine.execute();
    }

    std::cout << "Done rendering..." << std::endl;

    return 0;
}