#ifndef __VEC3_HPP__
#define __VEC3_HPP__

#include <cmath>
#include <ostream>

template <typename T>
struct Vec3
{

public:
    // Data & Constructors

    T x, y, z;

    Vec3(const T& x, const T& y, const T& z) :
        x { x }, y { y }, z { z }
    {
    }

    Vec3(const T& xyz) : 
        Vec3(xyz, xyz, xyz)
    {
    }

    Vec3() :
        Vec3(0)
    {
    }

public:

    friend std::ostream& operator<<(std::ostream& os, const Vec3& rhs)
    {
        return os << "[ " << rhs.x << ", " << rhs.y << ", " << rhs.z << " ]";
    }

    // Vector Math

    T dot(const Vec3& rhs) const
    {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    T operator%(const Vec3& rhs) const
    {
        return dot(rhs);
    }

    T length() const
    {
        return std::sqrt(dot(*this));
    }

    Vec3 normalized() const
    {
        return *this / length();
    }

    Vec3 operator!() const
    {
        return normalized();
    }

    Vec3 cross(const Vec3& rhs) const
    {
        return Vec3(
            y * rhs.z - z * rhs.y,
            z * rhs.x - x * rhs.z,
            x * rhs.y - y * rhs.x
        );
    }

    Vec3 operator^(const Vec3& rhs) const
    {
        return cross(rhs);
    }

public:
    // Arithmetic

    Vec3 operator+() const
    {
        return Vec3(+x, +y, +z);
    }

    Vec3 operator-() const
    {
        return Vec3(-x, -y, -z);
    }

    Vec3& operator+=(const Vec3& rhs)
    {
        x += rhs.x, y += rhs.y, z += rhs.z;
        return *this;
    }

    Vec3& operator-=(const Vec3& rhs)
    {
        x -= rhs.x, y -= rhs.y, z -= rhs.z;
        return *this;
    }

    Vec3& operator*=(const Vec3& rhs)
    {
        x *= rhs.x, y *= rhs.y, z *= rhs.z;
        return *this;
    }

    Vec3& operator/=(const Vec3& rhs)
    {
        x /= rhs.x, y /= rhs.y, z /= rhs.z;
        return *this;
    }

    // Use friend to get a copy of lhs
    friend Vec3 operator+(Vec3 lhs, const Vec3& rhs) 
    {
        return lhs += rhs;
    }

    friend Vec3 operator-(Vec3 lhs, const Vec3& rhs) 
    {
        return lhs -= rhs;
    }

    friend Vec3 operator*(Vec3 lhs, const Vec3& rhs) 
    {
        return lhs *= rhs;
    }

    friend Vec3 operator/(Vec3 lhs, const Vec3& rhs) 
    {
        return lhs /= rhs;
    }

};

// Common Typedefs
typedef Vec3<double> Vec3d;
typedef Vec3<float> Vec3f;

#endif