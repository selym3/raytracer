#include <iostream>

#include "gui/Engine.hpp"

int main(int argc, char** argv)
{
    // Define window size 
    std::size_t width = 640;
    std::size_t height = 480;
            
    // Define scene viewport
    double fov = 90.0;
    Camera camera = Camera(width, height, fov);

    // Create objects in scene
    std::vector<Shape> shapes;

    double z = 4;
    double r = 1;
    double s = 0.1;

    shapes.push_back(Shape(SphereCollider({-(r + s), 0, z}, r), Diffuse({64, 64, 64})));
    shapes.push_back(Shape(SphereCollider({+(r + s), 0, z}, r), Diffuse({128, 128, 128})));
    shapes.push_back(Shape(PlaneCollider({0, -(r + s),0}, {0,1,0}), Metal({0, 0, 0})));

    // Create light sources
    LightSet lights;

    lights.push_back({{0, r*3, z}, Vec3d{249, 252, 71}/3.0});

    // Define rendering options
    int max_depth = 8;
    int samples_per_pixel = 1;

    Vec3d background_color = Vec3d(158, 218, 255);

    // Create actual engine object
    Engine e = Engine(
        width, height,
        camera, background_color,
        shapes, lights,
        max_depth, samples_per_pixel
    );

    while (e.is_running())
    {
        e.update();
    }

    return 0;
}