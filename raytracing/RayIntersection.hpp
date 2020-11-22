#ifndef __RAY_INTERSECTION_HPP__
#define __RAY_INTERSECTION_HPP__

#include "./Shape.hpp"
#include "./Ray.hpp"

class Shape;

struct RayIntersection
{
    RayIntersection(const Shape& shape, const Ray& in, double t0, double t1);
    // RayIntersection(const Vec3& normal, const Vec3& hit, double t0, double t1);
    RayIntersection();

    /*
    If a ray had intersected with a shape.
    */
    bool intersected;
    
    /*
    If intersected is true, 
    t0 is ALWAYS guarnteed to be nonnegative
    
    This is implemented via the constructor
    */    
    double t0;
    double t1;

    Vec3 normal;
    Vec3 hit;

};

#endif