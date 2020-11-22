#include "../../math/Vec3.hpp"

#include <cmath>

Vec3::Vec3(double x, double y, double z): x {x}, y{y}, z{z} {}
Vec3::Vec3(double xyz): Vec3(xyz,xyz,xyz) {}
Vec3::Vec3(): Vec3(0) {}

Vec3& Vec3::operator+=(const Vec3& rhs) { x += rhs.x, y += rhs.y, z += rhs.z; return *this; }
Vec3& Vec3::operator-=(const Vec3& rhs) { x -= rhs.x, y -= rhs.y, z -= rhs.z; return *this; }
Vec3& Vec3::operator*=(const Vec3& rhs) { x *= rhs.x, y *= rhs.y, z *= rhs.z; return *this; }
Vec3& Vec3::operator/=(const Vec3& rhs) { x /= rhs.x, y /= rhs.y, z /= rhs.z; return *this; }

Vec3 operator+(Vec3 lhs, const Vec3& rhs) { return lhs += rhs; }
Vec3 operator-(Vec3 lhs, const Vec3& rhs) { return lhs -= rhs; }
Vec3 operator*(Vec3 lhs, const Vec3& rhs) { return lhs *= rhs; }
Vec3 operator/(Vec3 lhs, const Vec3& rhs) { return lhs /= rhs; }

double Vec3::dot(const Vec3& other) const { Vec3 tmp = (*this) * other; return tmp.x + tmp.y + tmp.z; }
double Vec3::dist(const Vec3& other) const
{
    Vec3 diff = (*this - other);
    double distSqr = diff.dot(diff);
    return std::sqrt(distSqr);
}
double Vec3::mag() const
{
    double distSqr = (*this).dot(*this);
    return std::sqrt(distSqr);
}
Vec3 Vec3::normalized() const { return (*this) / mag(); }