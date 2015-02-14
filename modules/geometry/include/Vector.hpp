#pragma once

#include <math/Real>

namespace geometry {

class Vector {
    using math::Real;
    
public:

    constexpr Vector(Real x, Real y, Real z) : _x(x), _y(y), _z(z) {}
    
    constexpr bool isNan() const {
        return _x != _x || _y != _y || _z != _z;
    }

private:

    Real _x;
    Real _y;
    Real _z;

};

}

