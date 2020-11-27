#ifndef __PERSPECTIVE_HPP__
#define __PERSPECTIVE_HPP__

#include "./Projection.hpp"

struct Perspective : public Projection {

    Perspective(double fov, int width, int height);
    ~Perspective()=default;

    Ray project(int x, int y) const;

private:
    double inverseWidth;
    double inverseHeight;
    double aspectRatio;
    double angle;
};

#endif
