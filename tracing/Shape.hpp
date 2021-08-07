#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__

#include <optional>

#include "Ray.hpp"
#include "Geometry.hpp"

struct Surface
{
    Vec3d color;
    Collision collision;

    Surface(const Vec3d& color, const Collision& collision) : 
        color{color}, collision{collision}
    {
    }
};

struct Shape
{
    // Data & Constructors

    Collider collider;
    Vec3d color;

    Shape(const Collider& collider, const Vec3d& color) : 
        collider { collider }, color { color }
    {
    }

public:
    // Ray Collisions

    std::optional<Surface> intersect(const Ray& ray) const
    {
        auto collision = collider(ray);
        
        if (!collision.has_value())
            return std::nullopt;

        Surface surface(
            color,
            collision.value()
        );

        return surface;
    }


};

#endif