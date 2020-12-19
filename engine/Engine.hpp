#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

#include <memory>
#include <vector>

#include "./projections/Camera.hpp"

#include "../raytracing/Sphere.hpp"
#include "../raytracing/Light.hpp"


struct Engine
{
    using ShapeType = Sphere;

    Engine(
        int width, 
        int height, 
        Light light,
        Camera camera
    );
    virtual ~Engine()=default;

    Engine& addShape(ShapeType shape);
    void clearShapes();

    virtual bool isRunning() const = 0;
    virtual void execute() = 0;

protected:

    using ShapeContainer = std::vector<ShapeType>;
    ShapeContainer shapes; 

protected:

    int width, height;

protected:

    Camera camera;

    Light light;

    Color backgroundColor = Vec3(1,1,1);
    Color trace(const Ray& in) const;

};

#endif