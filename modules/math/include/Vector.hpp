#pragma once

#include <math/Real>
#include <cmath>

namespace math {

class Vector {
    
public:

    constexpr Vector(Real x, Real y, Real z);
    
    constexpr bool isNan() const;

	constexpr Real x() const;
	constexpr Real y() const;
	constexpr Real z() const;

	constexpr Vector operator+(const Vector& vec) const;
	constexpr Vector operator-(const Vector& vec) const;
	
	constexpr Vector operator+() const;
	constexpr Vector operator-() const;
	
	constexpr Vector operator*(const Real& real) const;
	constexpr Vector operator/(const Real& real) const;
	
	/// Component-wise multiplication between vectors
	constexpr Vector operator*(const Vector& vec) const;
	
	/// Component-wise division between vectors
	constexpr Vector operator/(const Vector& vec) const;
	
	/// Component-wise multiplication between vectors
	constexpr Vector& operator*=(const Vector& vec);
	
	/// Component-wise division between vectors
	constexpr Vector& operator/=(const Vector& vec);
	
	constexpr Vector& operator+=(const Vector& vec);
	constexpr Vector& operator-=(const Vector& vec);
	constexpr Vector& operator*=(const Real& real);
	constexpr Vector& operator/=(const Real& real);
	
	constexpr bool operator>(const Vector& vec) const;
	constexpr bool operator<(const Vector& vec) const;
	constexpr bool operator>=(const Vector& vec) const;
	constexpr bool operator<=(const Vector& vec) const;
	
	/// The dot product of a vector with another vector
	constexpr Real dot(const Vector& vec) const;
	
	/// Returns the dot product of a vector with itself
	constexpr Real dotself() const;
	
	/// Returns the length of a vector
	Real length() const; // requires sqrt which is not constexpr. How fix?
	
	/// Returns the cross product of a vector
	constexpr Vector cross(const Vector& vec) const;

private:

    Real _x;
    Real _y;
    Real _z;
    
};

constexpr Vector::Vector(Real x, Real y, Real z) : _x(x), _y(y), _z(z) {
}

constexpr bool Vector::isNan() const {
	return _x != _x || _y != _y || _z != _z;
}
    
constexpr Real Vector::dot(const Vector& vec) const {
	return _x * vec._x + _y * vec._y + _z * vec._z;
}

constexpr Real Vector::dotself() const {
	return dot(*this);
}

Real Vector::length() const {
	return std::sqrt(dot(*this));
}

constexpr Vector Vector::cross(const Vector& vec) const {
	return {
		_y*vec._z - _z * vec._y,
		_z*vec._x - _x * vec._z,
		_x*vec._y - _y * vec._x
	};
}

constexpr Real Vector::x() const {
	return _x;
}

constexpr Real Vector::y() const {
	return _y;
}

constexpr Real Vector::z() const {
	return _z;
}

constexpr Vector Vector::operator+(const Vector& vec) const {
	return {_x + vec._x, _y + vec._y, _z + vec._z};
}

constexpr Vector Vector::operator-(const Vector& vec) const {
	return {_x - vec._x, _y - vec._y, _z - vec._z};
}

constexpr Vector Vector::operator+() const {
	return {_x, _y, _z};	// Nice isn't it? Use me! I am anxious to be used.
}

constexpr Vector Vector::operator-() const {
	return {-_x, -_y, -_z};
}

constexpr Vector Vector::operator*(const Vector& vec) const {
	return {_x * vec._x, _y * vec._y, _z * vec._z};
}

constexpr Vector Vector::operator*(const Real& real) const {
	return {_x * real, _y * real, _z * real};
}

constexpr Vector Vector::operator/(const Vector& vec) const {
	return {_x / vec._x, _y / vec._x, _z / vec._z};
}

constexpr Vector Vector::operator/(const Real& real) const {
	return {_x / real, _y / real, _z / real};
}

constexpr Vector& Vector::operator+=(const Vector& vec) {
	_x += vec._x;
	_y += vec._y;
	_z += vec._z;
	return *this;
}

constexpr Vector& Vector::operator-=(const Vector& vec) {
	_x -= vec._x;
	_y -= vec._y;
	_z -= vec._z;
	return *this;
}

constexpr Vector& Vector::operator*=(const Vector& vec) {
	_x *= vec._x;
	_y *= vec._y;
	_z *= vec._z;
	return *this;
}

constexpr Vector& Vector::operator/=(const Vector& vec) {
	_x /= vec._x;
	_y /= vec._y;
	_z /= vec._z;
	return *this;
}

constexpr Vector& Vector::operator*=(const Real& real) {
	_x *= real;
	_y *= real;
	_z *= real;
	return *this;
}

constexpr Vector& Vector::operator/=(const Real& real) {
	_x /= real;
	_y /= real;
	_z /= real;
	return *this;
}

constexpr bool Vector::operator>(const Vector& vec) const {
	return dotself() > vec.dotself();
}

constexpr bool Vector::operator<(const Vector& vec) const {
	return dotself() < vec.dotself();
}

constexpr bool Vector::operator>=(const Vector& vec) const {
	return dotself() >= vec.dotself();
}

constexpr bool Vector::operator<=(const Vector& vec) const {
	return dotself() <= vec.dotself();
}

} // math namespace

