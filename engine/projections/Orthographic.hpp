#ifndef __ORTHOGRAPHIC_HPP__
#define __ORTHOGRAPHIC_HPP__

#include "./Projection.hpp"

struct Orthographic : public Projection {

    Orthographic(int width, int height);
    ~Orthographic()=default;

    Ray project(int x, int y) const;

private:
    int width, height;

};

#endif