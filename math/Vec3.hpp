#ifndef __VEC3_HPP__
#define __VEC3_HPP__

// #include <SFML/System/Vector3.hpp>
// using Vec3 = sf::Vector3<double>;

double to_radians(double degrees);
double to_degrees(double radians);

struct Vec3
{

    double x, y, z;

    Vec3(double x, double y, double z);
    Vec3(double xyz);
    Vec3();

    Vec3 &operator+=(const Vec3 &rhs);
    Vec3 &operator-=(const Vec3 &rhs);
    Vec3 &operator*=(const Vec3 &rhs);
    Vec3 &operator/=(const Vec3 &rhs);

    friend Vec3 operator+(Vec3 lhs, const Vec3 &rhs);
    friend Vec3 operator-(Vec3 lhs, const Vec3 &rhs);
    friend Vec3 operator*(Vec3 lhs, const Vec3 &rhs);
    friend Vec3 operator/(Vec3 lhs, const Vec3 &rhs);

    Vec3 rotate(double pitch, double yaw, double roll, Vec3 around = 0) const;

    double dot(const Vec3 &other) const;
    double dist(const Vec3 &other) const;
    double mag() const;
    Vec3 normalized() const;
};

#endif