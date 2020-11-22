#ifndef __RAY_HPP__
#define __RAY_HPP__

#include "../math/Vec3.hpp"

class Ray
{
    /*
    Store origin and destination. Neither of these points
    are defined relative to each other.
    */
    Vec3 m_origin;
    Vec3 m_destination;

public:
    Ray(const Vec3 &origin, const Vec3 &direction);

    Ray& setOrigin(const Vec3& origin);
    Ray& setDestination(const Vec3& dest);
    Ray& setDirection(const Vec3& dir);

    const Vec3& origin() const;
    const Vec3& destination() const;
    Vec3 direction() const;

    Vec3 sample(double t) const;
};

#endif