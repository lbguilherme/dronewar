#pragma once

#include <math/Real>
#include <cmath>
#include <stdexcept>

namespace math {

class Vector {

public:

	constexpr Vector();
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

constexpr Vector operator*(const Real& real, const Vector& vec);
constexpr Vector& operator*=(const Real& real, const Vector& vec);

constexpr Vector operator*(const Real& real, const Vector& vec) {
	return vec * real;
}

constexpr Vector& operator*=(const Real& real, Vector& vec) {
	return vec *= real;
}

inline constexpr Vector::Vector() : _x(), _y(), _z() {

}

inline constexpr Vector::Vector(Real x, Real y, Real z) : _x(x), _y(y), _z(z) {

}

inline constexpr bool Vector::isNan() const {
	return _x != _x || _y != _y || _z != _z;
}

inline constexpr Real Vector::dot(const Vector& vec) const {
	return _x * vec._x + _y * vec._y + _z * vec._z;
}

inline constexpr Real Vector::dotself() const {
	return dot(*this);
}

inline Real Vector::length() const {
	return std::sqrt(dot(*this));
}

inline constexpr Vector Vector::cross(const Vector& vec) const {
	return {
		_y*vec._z - _z * vec._y,
		_z*vec._x - _x * vec._z,
		_x*vec._y - _y * vec._x
	};
}

inline constexpr Real Vector::x() const {
	return _x;
}

inline constexpr Real Vector::y() const {
	return _y;
}

inline constexpr Real Vector::z() const {
	return _z;
}

inline constexpr Vector Vector::operator+(const Vector& vec) const {
	return {_x + vec._x, _y + vec._y, _z + vec._z};
}

inline constexpr Vector Vector::operator-(const Vector& vec) const {
	return {_x - vec._x, _y - vec._y, _z - vec._z};
}

inline constexpr Vector Vector::operator+() const {
	return {_x, _y, _z};	// Nice isn't it? Use me! I am anxious to be used.
}

inline constexpr Vector Vector::operator-() const {
	return {-_x, -_y, -_z};
}

inline constexpr Vector Vector::operator*(const Vector& vec) const {
	return {_x * vec._x, _y * vec._y, _z * vec._z};
}

inline constexpr Vector Vector::operator*(const Real& real) const {
	return {_x * real, _y * real, _z * real};
}

inline constexpr Vector Vector::operator/(const Vector& vec) const {
	#ifdef DEBUG
	if (vec.x() == 0 || vec.y() == 0 || vec.z() == 0) throw std::logic_error("Can't divide by zero");
	#endif

	return {_x / vec._x, _y / vec._y, _z / vec._z};
}

inline constexpr Vector Vector::operator/(const Real& real) const {
	#ifdef DEBUG
	if (real == 0) throw std::logic_error("Can't divide by zero");
	#endif

	return {_x / real, _y / real, _z / real};
}

inline constexpr Vector& Vector::operator+=(const Vector& vec) {
	_x += vec._x;
	_y += vec._y;
	_z += vec._z;
	return *this;
}

inline constexpr Vector& Vector::operator-=(const Vector& vec) {
	_x -= vec._x;
	_y -= vec._y;
	_z -= vec._z;
	return *this;
}

inline constexpr Vector& Vector::operator*=(const Vector& vec) {
	_x *= vec._x;
	_y *= vec._y;
	_z *= vec._z;
	return *this;
}

inline constexpr Vector& Vector::operator/=(const Vector& vec) {
	#ifdef DEBUG
	if (vec.x() * vec.y() * vec.z() == 0) throw std::logic_error("Can't divide by zero");
	#endif

	_x /= vec._x;
	_y /= vec._y;
	_z /= vec._z;
	return *this;
}

inline constexpr Vector& Vector::operator*=(const Real& real) {
	_x *= real;
	_y *= real;
	_z *= real;
	return *this;
}

inline constexpr Vector& Vector::operator/=(const Real& real) {
	#ifdef DEBUG
	if (real == 0) throw std::logic_error("Division by zero. Invalid real number");
	#endif

	_x /= real;
	_y /= real;
	_z /= real;
	return *this;
}

inline constexpr bool Vector::operator>(const Vector& vec) const {
	return dotself() > vec.dotself();
}

inline constexpr bool Vector::operator<(const Vector& vec) const {
	return dotself() < vec.dotself();
}

inline constexpr bool Vector::operator>=(const Vector& vec) const {
	return dotself() >= vec.dotself();
}

inline constexpr bool Vector::operator<=(const Vector& vec) const {
	return dotself() <= vec.dotself();
}

} // math namespace

