#include "../../raytracing/Ray.hpp"

Ray::Ray(const Vec3& o, const Vec3& dir) : m_origin { o }, m_destination { o + dir } {}

Vec3 Ray::sample(double t) const
{
    return (1-t) * m_origin + t * m_destination;
}

Ray &Ray::setOrigin(const Vec3 &origin)
{
    m_origin = origin;
    return *this;
}
Ray &Ray::setDestination(const Vec3 &dest)
{
    m_destination = dest;
    return *this;
}
Ray &Ray::setDirection(const Vec3 &dir)
{
    m_destination = (m_origin + dir);
    return *this;
}

const Vec3 &Ray::origin() const { return m_origin; }
const Vec3 &Ray::destination() const { return m_destination; }
Vec3 Ray::direction() const { return (m_destination - m_origin); }