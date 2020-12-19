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

    constexpr int WIDTH  = 300;
    constexpr int HEIGHT = 300;

    SFML_Engine engine {
        WIDTH,
        HEIGHT,
        Camera(
            Perspective(
                90, 
                WIDTH, 
                HEIGHT
            )
        ),
        Light(
            Vec3(-300, 600, 30)
        ),
        1
    };

    engine
        .addShape(Sphere(Vec3( 0, -2.5, -15), 4, Material(Color(1, 0, 0))))
        .addShape(Sphere(Vec3( 0, 2.5, -45), 12, Material(Color(1,0,1))));
        // .addShape(Sphere(Vec3( 0, -9000, 0), 9000 - 0.7, Material(Color(1,1,1))));

    std::cout << "Start rendering...\n";

    while (engine.isRunning()) {
        engine.execute();
    }

    std::cout << "Done rendering..." << std::endl;

    return 0;
}