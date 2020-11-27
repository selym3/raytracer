#include "../../raytracing/RayIntersection.hpp"
#include "../../raytracing/Shape.hpp"

RayIntersection::RayIntersection() : intersected { false } {}
RayIntersection::RayIntersection(const Vec3& hit, const Vec3& normal, double t0) : 
    intersected { true }, 
    t0 { t0 },
    hit { hit },
    normal { normal }
{
}

// RayIntersection::RayIntersection(const Shape &shape, const Ray &ray, double t0) : 
//     t0 { t0 }
// {
//     hit = ray.sample(t0);
//     normal = shape.calculateNormal(hit);
// }