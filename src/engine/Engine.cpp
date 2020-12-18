#include "../../engine/Engine.hpp"

Engine::Engine(
    int width, 
    int height, 
    Light light,
    Camera camera
) : width { width },
    height { height },
    camera { camera },
    light { light }
{
}

Engine& Engine::addShape(Engine::ShapeType newShape)
{
    shapes.push_back(newShape);

    return *this;
}

void Engine::clearShapes()
{
    shapes.clear();
}
#include <iostream>
Color Engine::trace(const Ray& in) const 
{

    RayIntersection nearest;
    const Shape * shapeHit = nullptr;

    for (const auto& shape : shapes) {

        auto tmp = shape.intersect(in);

        if (tmp.intersected && (!shapeHit || tmp.t0 < nearest.t0)) {
            nearest = tmp;
            shapeHit = &shape;
        }
    }

    if (!shapeHit) {
    
        return this->backgroundColor;
    
    }

    Ray shadowRay(nearest.hit, this->light - nearest.hit);
    double inShadow = 1;

    for (const auto& shape : shapes) {
        if (&shape != shapeHit) {
            auto tmp = shape.intersect(shadowRay);
            if  (tmp.intersected) {
                inShadow = 0;
                break;
            }
        }
    }

    return shapeHit->color() * inShadow;
    
}