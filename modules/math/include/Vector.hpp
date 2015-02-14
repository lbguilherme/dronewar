#pragma once

#include <math/Real>

namespace math {

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

public:
	Real x() const;
	Real y() const;
	Real z() const;

	Vector operator+(const Vector& vec) const;
	Vector operator-(const Vector& vec) const;
	
	Vector operator+() const;
	Vector operator-() const;
	
	Vector operator*(const Real& real) const;
	Vector operator/(const Real& real) const;
	
	/// Component-wise multiplication between vectors
	Vector operator*(const Vector& vec) const;
	
	/// Component-wise division between vectors
	Vector operator/(const Vector& vec) const;
	
	/// Component-wise multiplication between vectors
	Vector& operator*=(const Vector& vec);
	
	/// Component-wise division between vectors
	Vector& operator/=(const Vector& vec);
	
	Vector& operator+=(const Vector& vec);
	Vector& operator-=(const Vector& vec);
	Vector& operator*=(const Real& real);
	Vector& operator/=(const Real& real);
	
	bool operator>(const Vector& vec) const;
	bool operator<(const Vector& vec) const;
	bool operator>=(const Vector& vec) const;
	bool operator<=(const Vector& vec) const;
	
	/// The dot product of a vector with another vector
	Real dot(const Vector& vec) const;
	
	/// Returns the dot product of a vector with itself
	Real dotself(const Vector& vec) const;
	
	/// Returns the length of a vector
	Real length() const;
	
	/// Returns the cross product of a vector
	Vector cross(const Vector& vec) const;
};

}

