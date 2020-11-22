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
    return RayIntersection(
        *this,
        in,
        tca - thc,
        tca + thc
    );
}

Vec3 Sphere::calculateNormal(const Vec3& a) const 
{
    return (a - m_origin).normalized();  
}