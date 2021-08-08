#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__

#include <vector>
#include <functional>

#include "Light.hpp"

#include "Vec3.hpp"
#include "Ray.hpp"
#include "Geometry.hpp"

struct SurfaceColor
{
    Vec3d color;
    std::vector<Ray> rays;
    double absorption; // <-- how much of each ray color to use

    SurfaceColor(const Vec3d& color, const std::vector<Ray>& rays, double absorption = 1.0) :
        color { color }, rays { rays }, absorption { absorption }
    {
    }

    SurfaceColor(const Vec3d& color) :
        SurfaceColor(color, std::vector<Ray>{}, 0)
    {
    }

};

using Material = std::function<SurfaceColor(const Ray&, const Collision&, const LightSet&)>;

struct Diffuse
{
    Vec3d ambient;

    Diffuse(const Vec3d& ambient) :
        ambient{ambient}
    {
    }

    SurfaceColor operator()(const Ray& incoming, const Collision& surface, const LightSet& lights) const
    {
        Vec3d result = ambient;

        // for (const auto& light : lights)
        // {
        //     auto p = surface.normal % (light.position - surface.where);
        //     result += light.color * p;
        // }

        return result;
    }

};

struct Metal 
{
    Vec3d color;

    Metal(const Vec3d& color) :
        color{color}
    {
    }

    SurfaceColor operator()(const Ray& incoming, const Collision& surface, const LightSet&) const
    {
        std::vector<Ray> rays;
        rays.push_back(incoming.reflect(surface.where, surface.normal, 0.01));

        SurfaceColor out(color, rays, 0.5);
        return out;
    }

};



#endif