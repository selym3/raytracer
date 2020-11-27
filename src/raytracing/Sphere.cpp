#include "../../raytracing/Sphere.hpp"
#include <cmath> 
Sphere::Sphere(const Vec3& origin, double r, const Color& color)
    : Shape(color), radius { r }, m_origin { origin }
{
}

Sphere::~Sphere() {}

RayIntersection Sphere::intersect(const Ray& in) const
{
    auto l = m_origin - in.origin();
    auto tca = l.dot(in.direction());
    if (tca < 0) return RayIntersection();
    auto d2 = l.dot(l) - tca * tca;
    if (d2 > radius * radius) return RayIntersection();
    auto thc = std::sqrt(radius * radius - d2);
    
    auto t0 = tca - thc;
    auto t1 = tca + thc;
    if (t0 < t1) t0 = t1;

    auto hit = in.sample(t0);
    return RayIntersection(
        hit, 
        (hit - m_origin).normalized(), 
        t0
    );
}

Vec3 Sphere::calculateNormal(const Vec3& a) const 
{
    return (a - m_origin).normalized();  
}