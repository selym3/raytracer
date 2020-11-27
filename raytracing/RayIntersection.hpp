#ifndef __RAY_INTERSECTION_HPP__
#define __RAY_INTERSECTION_HPP__

#include "./Shape.hpp"
#include "./Ray.hpp"

class Shape;

struct RayIntersection
{

    /*
    Forces a true value with all the necessary data.
    */
    RayIntersection(const Vec3 &normal, const Vec3 &hit, double t0);

    /*
    Forces a false intersected value.
    */
    RayIntersection();

    /*
    If a ray had intersected with a shape.
    */
    bool intersected;

    /*
    This is the point on the ray that the shape intersected.
    
    The ray is not stored in this class, meaning that it can only
    be used in certain circumstancs where you know you are working on 
    the same ray. It can save time to compare the t0 value rather than the
    hit vector.
    */
    double t0;

    /*
    Point that the sphere was hit.
    */
    Vec3 hit;

    /*
    Collision normal.
    */
    Vec3 normal;
};

#endif