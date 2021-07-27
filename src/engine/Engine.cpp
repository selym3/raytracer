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

#include <cmath>

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
    
    
    Vec3 shifted = nearest.hit;// + 1e-5 * nearest.normal;
    Vec3 lightDirection = (this->light.position - shifted).normalized();
    Ray shadowRay(shifted, lightDirection);
    bool inShadow = false;

    for (const auto& shape : shapes) {
        auto tmp = shape.intersect(shadowRay);
        if ((&shape != shapeHit) && tmp.intersected) {
            inShadow = true;
            break;
        }
    }


    if (!inShadow) {
        Color illumination = 0;
        const auto& mat = shapeHit->material();

        illumination += mat.ambient * light.material.ambient;
        illumination += mat.diffuse * light.material.diffuse * lightDirection.dot(nearest.normal);

        auto h = (camera.translation - nearest.hit).normalized();
        h += lightDirection;
        h = h.normalized();

        illumination += mat.specular * light.material.specular * std::pow(nearest.normal.dot(h), mat.shininess / 4.0);
       
        illumination.x = illumination.x > 1 ? 1 : illumination.x < 0 ? 0 : illumination.x;
        illumination.y = illumination.y > 1 ? 1 : illumination.y < 0 ? 0 : illumination.y; 
        illumination.z = illumination.z > 1 ? 1 : illumination.z < 0 ? 0 : illumination.z;

        return illumination;

    } else {

        return Color(0,0,0);
    
    }
}