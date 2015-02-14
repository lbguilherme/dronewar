#pragma once

#include <math/Real>
using namespace math;

class Vector {
public:

    Vector(Real x, Real y, Real z) : _x(x), _y(y), _z(z) {
    }
    
    bool isNan() {
        return _x != _x || _y != _y || _z != _z;
    }

private:

    Real _x;
    Real _y;
    Real _z;

};

