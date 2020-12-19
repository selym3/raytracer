#ifndef __SPHERE_HPP__
#define __SPHERE_HPP__

#include "./Shape.hpp"

class Sphere : public Shape 
{

    Vec3 m_origin;
    double radius;

public:
    Sphere(const Vec3& origin, double r, const Material& material);
    ~Sphere();

    RayIntersection intersect(const Ray& in) const;

protected:

    // returns a normalized normal
    Vec3 calculateNormal(const Vec3& a) const;

};

#endif