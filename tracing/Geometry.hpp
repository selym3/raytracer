#ifndef __GEOMETRY_HPP__
#define __GEOMETRY_HPP__

#include <cmath>
#include <optional>
#include <functional>

#include "Ray.hpp"
#include "Vec3.hpp"

// Represents a collision between a ray and shape
struct Collision
{
    double sample;
    Vec3d where, normal;

    Collision(double sample, Vec3d where, Vec3d normal) :
        sample{sample}, where{where}, normal{!normal}
    {
    }

    bool operator<(const Collision& rhs) const
    {
        return sample < rhs.sample;
    }
};

// Allows for the returning of a null collision
using CollisionTest = std::optional<Collision>;

// Lambda for any geometry that intersects with a ray
using Collider = std::function<CollisionTest(const Ray&)>;

// Sphere / Ray collision tester
struct SphereCollider
{
    // Data to represent a sphere
    Vec3d center;
    double r;

    // Create sphere collider
    SphereCollider(const Vec3d& center, double r) :
        center{center}, r{r}
    {
    }

    // Performs collision algorithm
    CollisionTest operator()(const Ray& ray) const
    {
        // The equation of a sphere in vector form is 
        //  (P-C) dot (P-C) = r^2 
        //  (can be derived from the non-vector equation for a sphere)
        // where P is any point and 
        // C is the center of the sphere

        // The ray is 
        //  P(t) = O + tD
        // where O is the origin and D is the direction
        // This equation can be plugged in for P
        // (P(t) - C) dot (P(t) - C) = r^2 so that t can be solved for

        // Expanding the above equations gets 
        //  (O + tD - C) dot (O + tD - C) = r^2
        // Expanding more according to vector algebra gets 
        //  (t^2 * (D dot D)) + (t * (2 * D dot (A-C))) + ((A-C) dot (A-C)) - r ^ 2 = 0
        
        // Setup repeated values (vectors)
        const auto& D = ray.direction;
        const auto AC = ray.origin - center;

        // Calculate a, b, c into quadratic formula (doubles)
        const auto a = D % D;
        const auto b = 2 * (D % AC);
        const auto c = (AC % AC) - (r * r);

        // With this comes a quadratic equation to plug into 
        // the quadratic formula, where discriminant can be 
        // used to see if any intersections at all. 

        // Calculate discriminant (double)
        const auto discriminant = b*b - 4*a*c;
        
        if (discriminant < 0)
            return std::nullopt;

        // If there are roots, calculate
        auto dsqrt = std::sqrt(discriminant);

        auto t0 = (-b - dsqrt) / (2 * a);
        auto t1 = (-b + dsqrt) / (2 * a);

        // t1 is always greater than t0, so if it's behind the 
        // origin, discard this ray
        if (t1 < 0) 
            return std::nullopt;
        
        // If the roots are reveresed (for some reason), swap them to 
        // get the smaller root in t0
        if (t0 > t1) 
            t0 = t1;

        // Create a collision object to return
        auto where = ray.sample(t0);

        // TODO: using the dot product with the ray direction, it can be
        // determined if the normal is facing away / towards the camera
        auto normal = where - center;

        return Collision(t0, where, normal);
    }
};

// Plane/Ray Collision Tester
struct PlaneCollider
{
    // Data to represent a plane
    Vec3d point, normal;

    // Create a plane collider
    PlaneCollider(const Vec3d& point, const Vec3d& normal) :
        point{point}, normal{!normal}
    {
    }

    PlaneCollider(double offset, const Vec3d& normal) :
        PlaneCollider(Vec3d(0, offset, 0), normal)
    {
    }

    CollisionTest operator()(const Ray& ray) const
    {
        // Knowing that (A dot B) = 0 if A and B are perpendicular, 
        // and that a plane is vector P away from the origin facing 
        // unit vector N, 
        // 
        // (X - P) dot N = 0, where X is any point because any point
        // on the plane will be perpendicular to the plane's normal
        
        // Knowing that a ray is X(t) = A + t*D, the intersection of a plane
        // and ray becomes 
        //  (X(t) - P) dot N = 0
        //  (A + t*D) dot N = 0

        const auto& D = ray.direction;

        // Solving for t yields
        //  ((t * D) dot N) + ((A - P) dot N) = 0
        //  t = ((P - A) dot N) / (D dot N)
        
        const auto denominator = normal % D;

        // Note that when the denominator (D dot N) approaches zero, 
        // the plane and the ray perfectly coincide, so an epsilon should be used
        // to handle this code

        const static auto RAY_EPSILON = 1e-6;

        // Reject rays that miss because they are parallel to the plane (dot product is near 0)
        if (std::abs(denominator) <= RAY_EPSILON)
            return std::nullopt;
        
        const auto diff = point - ray.origin;
        const auto t = (diff % normal) / denominator;

        // Reject rays that are behind the origin
        if (t < 0)
            return std::nullopt;

        // Create a collision object
        auto where = ray.sample(t);

        // TODO: using the dot product with the ray direction, it can be
        // determined if the normal is facing away / towards the camera
        const auto& n = normal; 

        return Collision(t, where, n);
    }


};

#endif