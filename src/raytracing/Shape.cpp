#include "../../raytracing/Shape.hpp"

Shape::Shape(const Vec3 &color) : m_color{color} {}
Shape::~Shape() {}


Vec3 Shape::calculateNormal(const Ray& in, double t) const 
{
    return this->calculateNormal(in.sample(t));
}

const Vec3& Shape::color() const { return m_color; }