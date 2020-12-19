#include "../../raytracing/Shape.hpp"

Shape::Shape(const Material &color) : m_material{color} {}
Shape::~Shape() {}
const Material& Shape::material() const { return m_material; }