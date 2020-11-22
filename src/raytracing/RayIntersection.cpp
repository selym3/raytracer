#include "../../raytracing/RayIntersection.hpp"
#include "../../raytracing/Shape.hpp"

RayIntersection::RayIntersection() : intersected { false } {}
RayIntersection::RayIntersection(const Shape& sIn, const Ray& in, double t0, double t1) : 
    intersected { true }, 
    t0 { t0 }, 
    t1 {t1}
{
    auto tmp = t0;
    if (t0 < t1) t0 = t1, t1 = tmp;

    hit = in.sample(t0);
    normal = sIn.calculateNormal(hit);
}

// RayIntersection::RayIntersection(const Vec3& hit, const Vec3& normal, double t0, double t1) :
//     intersected { true },
//     t0 { t0 },
//     t1 { t1 },
//     hit { hit },
//     normal { normal }
// {
//     auto tmp = t0;
//     if (t0 < t1) t0 = t1, t1 = tmp;
// }