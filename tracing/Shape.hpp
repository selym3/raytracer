#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__

#include <optional>

#include "Ray.hpp"
#include "Geometry.hpp"
#include "Material.hpp"

struct Surface
{
    Material material;
    Collision collision;

    Surface(const Material& material, const Collision& collision) : 
        material{material}, collision{collision}
    {
    }

    SurfaceColor getSurfaceColor(const Ray& incoming, const LightSet& lightset) const
    {
        return material(incoming, collision, lightset);
    }
};

struct Shape
{
    // Data & Constructors

    Collider collider;
    Material material;

    Shape(const Collider& collider, const Material& material) : 
        collider { collider }, material { material }
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
            material,
            collision.value()
        );

        return surface;
    }


};

#endif