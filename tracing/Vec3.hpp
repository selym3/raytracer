#ifndef __VEC3_HPP__
#define __VEC3_HPP__

#include <cmath>

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
    // Vector Math

    T dot(const Vec3& rhs) const
    {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    T length() const
    {
        return std::sqrt(dot(*this));
    }

    Vec3 normalized() const
    {
        return *this / length();
    }

public:
    // Arithmetic

    Vec3 operator-() const
    {
        return Vec3(-x, -y, -z);
    }

    Vec3& operator+=(const Vec3& rhs)
    {
        x += rhs.x, y += rhs.y;
        return *this;
    }

    Vec3& operator-=(const Vec3& rhs)
    {
        x -= rhs.x, y -= rhs.y;
        return *this;
    }

    Vec3& operator*=(const Vec3& rhs)
    {
        x *= rhs.x, y *= rhs.y;
        return *this;
    }

    Vec3& operator/=(const Vec3& rhs)
    {
        x /= rhs.x, y /= rhs.y;
        return *this;
    }

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