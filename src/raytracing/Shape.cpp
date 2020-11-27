#include "../../raytracing/Shape.hpp"

Shape::Shape(const Vec3 &color) : m_color{color} {}
Shape::~Shape() {}
const Color& Shape::color() const { return m_color; }