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

double to_radians(double degrees) { return degrees * M_PI / 180.0; }
double to_degrees(double radians) { return radians * 180.0 / M_PI; }

Vec3 Vec3::rotate(double yaw, double pitch, double roll, Vec3 around) const
{
    yaw = to_radians(yaw);
    roll = to_radians(roll);
    pitch = to_radians(pitch);

    Vec3 out = *this - around;
    
    // rotate around the z axis
    out = Vec3(
        out.x * std::cos(yaw) - out.y * std::sin(yaw),
        out.x * std::sin(yaw) + out.y * std::cos(yaw),
        out.z
    );

    // rotate around the y axis
    out = Vec3(
        out.x * std::cos(pitch) + out.z * std::cos(pitch),
        out.y,
        -out.x * std::sin(pitch) + out.z * std::cos(pitch)
    );

    // rotate around the x axis
    out = Vec3(
        out.x,
        out.y * std::cos(roll) - out.z * std::sin(roll),
        out.y * std::sin(roll) + out.z * std::cos(roll)
    );

    return out += around;
}