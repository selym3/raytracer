#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

#include <memory>
#include <vector>

#include "./projections/Projection.hpp"
#include "./projections/Perspective.hpp"
#include "./projections/Orthographic.hpp"

#include "../raytracing/Sphere.hpp"

#include "../raytracing/Shape.hpp"

struct Engine
{
    // using Projector = Perspective;

    // std::unique_ptr<Projection> rayProjector;

    using ProjectorType = Perspective;
    using ShapeType = Sphere;
    using Light = Vec3;

    Engine(
        int width, 
        int height, 
        Light light,
        ProjectorType prj
    );

    Engine& addShape(ShapeType shape);

    void clearShapes();

    virtual ~Engine()=default;

    virtual bool isRunning() const = 0;
    
    virtual void execute() = 0;

protected:

    using ShapeContainer = std::vector<ShapeType>;

    ProjectorType projector;
    ShapeContainer shapes; 

protected:

    int width, height;

protected:

    Light light;

    Color backgroundColor = 1;

    Color trace(const Ray& in) const;

};

#endif