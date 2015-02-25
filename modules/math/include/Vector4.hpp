#pragma once

#include <math/Real>
#include <cmath>
#include <stdexcept>

namespace math {

class Vector4 {

public:

	constexpr Vector4();
	constexpr Vector4(Real x, Real y, Real z, Real t);

	constexpr bool isNan() const;

	constexpr Real x() const;
	constexpr Real y() const;
	constexpr Real z() const;
	constexpr Real t() const;
	
	constexpr const Real& operator()(unsigned i) const;
	constexpr Real& operator()(unsigned i);

	constexpr Vector4 operator+(const Vector4& vec) const;
	constexpr Vector4 operator-(const Vector4& vec) const;
	
	constexpr Vector4 operator+() const;
	constexpr Vector4 operator-() const;
	
	constexpr Vector4 operator*(const Real& real) const;
	constexpr Vector4 operator/(const Real& real) const;
	
	/// Component-wise multiplication between Vector4s
	constexpr Vector4 operator*(const Vector4& vec) const;
	
	/// Component-wise division between Vector4s
	constexpr Vector4 operator/(const Vector4& vec) const;
	
	/// Component-wise multiplication between Vector4s
	constexpr Vector4& operator*=(const Vector4& vec);
	
	/// Component-wise division between Vector4s
	constexpr Vector4& operator/=(const Vector4& vec);
	
	constexpr Vector4& operator+=(const Vector4& vec);
	constexpr Vector4& operator-=(const Vector4& vec);
	constexpr Vector4& operator*=(const Real& real);
	constexpr Vector4& operator/=(const Real& real);
	
	constexpr bool operator>(const Vector4& vec) const;
	constexpr bool operator<(const Vector4& vec) const;
	constexpr bool operator>=(const Vector4& vec) const;
	constexpr bool operator<=(const Vector4& vec) const;
	constexpr bool operator==(const Vector4& vec) const;
	
	/// The dot product of a Vector4 with another Vector4
	constexpr Real dot(const Vector4& vec) const;
	
	/// Returns the dot product of a Vector4 with itself
	constexpr Real dotself() const;
	
	/// Returns the length of a Vector4
	Real length() const; // requires sqrt which is not constexpr. How fix?
	
	/// Returns the cross product of a Vector4
	constexpr Vector4 cross(const Vector4& vec) const;
	
	/// Returns the unit Vector4
	constexpr Vector4 unit() const;

private:

	Real _x;
	Real _y;
	Real _z;
	Real _t;

};

constexpr Vector4 operator*(const Real& real, const Vector4& vec);

constexpr Vector4 operator*(const Real& real, const Vector4& vec) {
	return vec * real;
}

inline constexpr Vector4::Vector4() : _x(), _y(), _z(), _t() {

}

inline constexpr Vector4::Vector4(Real x, Real y, Real z, Real t) : _x(x), _y(y), _z(z), _t(t) {

}

inline constexpr bool Vector4::isNan() const {
	return _x != _x || _y != _y || _z != _z || _t != _t;
}

inline constexpr Real Vector4::dot(const Vector4& vec) const {
	return _x * vec._x + _y * vec._y + _z * vec._z + _t * vec._t;
}

inline constexpr Real Vector4::dotself() const {
	return dot(*this);
}

inline Real Vector4::length() const {
	return std::sqrt(dot(*this));
}

inline constexpr Vector4 Vector4::cross(const Vector4& vec) const {
	return {
		_y*vec._z - _z * vec._y,
		_z*vec._x - _x * vec._z,
		_x*vec._y - _y * vec._x,
		vec._t
	};
}

inline constexpr Vector4 Vector4::unit() const {
	return (*this) / length();
}

inline constexpr Real Vector4::x() const {
	return _x;
}

inline constexpr Real Vector4::y() const {
	return _y;
}

inline constexpr Real Vector4::z() const {
	return _z;
}

inline constexpr Real Vector4::t() const {
	return _t;
}

inline constexpr const Real& Vector4::operator()(unsigned i) const {
	switch (i) {
		case 0: return _x;
		case 1: return _y;
		case 2: return _z;
		case 3: return _t;
	}
	throw std::logic_error("Invalid index");
}

inline constexpr Real& Vector4::operator()(unsigned i) {
	switch (i) {
		case 0: return _x;
		case 1: return _y;
		case 2: return _z;
		case 3: return _t;
	}
	throw std::logic_error("Invalid index");
}

inline constexpr Vector4 Vector4::operator+(const Vector4& vec) const {
	return {_x + vec._x, _y + vec._y, _z + vec._z, _t + vec._t};
}

inline constexpr Vector4 Vector4::operator-(const Vector4& vec) const {
	return {_x - vec._x, _y - vec._y, _z - vec._z, _t - vec._t};
}

inline constexpr Vector4 Vector4::operator+() const {
	return {_x, _y, _z, _t};	// Nice isn't it? Use me! I am anxious to be used.
}

inline constexpr Vector4 Vector4::operator-() const {
	return {-_x, -_y, -_z, -_t};
}

inline constexpr Vector4 Vector4::operator*(const Vector4& vec) const {
	return {_x * vec._x, _y * vec._y, _z * vec._z, _t * vec._t};
}

inline constexpr Vector4 Vector4::operator*(const Real& real) const {
	return {_x * real, _y * real, _z * real, _t * real};
}

inline constexpr Vector4 Vector4::operator/(const Vector4& vec) const {
	#ifdef DEBUG
	if (vec.x() == 0 || vec.y() == 0 || vec.z() == 0 || vec.t() == 0) throw std::logic_error("Can't divide by zero");
	#endif

	return {_x / vec._x, _y / vec._y, _z / vec._z, _t / vec._t};
}

inline constexpr Vector4 Vector4::operator/(const Real& real) const {
	#ifdef DEBUG
	if (real == 0) throw std::logic_error("Can't divide by zero");
	#endif

	return {_x / real, _y / real, _z / real, _t / real};
}

inline constexpr Vector4& Vector4::operator+=(const Vector4& vec) {
	_x += vec._x;
	_y += vec._y;
	_z += vec._z;
	_t += vec._t;
	return *this;
}

inline constexpr Vector4& Vector4::operator-=(const Vector4& vec) {
	_x -= vec._x;
	_y -= vec._y;
	_z -= vec._z;
	_t -= vec._t;
	return *this;
}

inline constexpr Vector4& Vector4::operator*=(const Vector4& vec) {
	_x *= vec._x;
	_y *= vec._y;
	_z *= vec._z;
	_t *= vec._t;
	return *this;
}

inline constexpr Vector4& Vector4::operator/=(const Vector4& vec) {
	#ifdef DEBUG
	if (vec.x() * vec.y() * vec.z() == 0) throw std::logic_error("Can't divide by zero");
	#endif

	_x /= vec._x;
	_y /= vec._y;
	_z /= vec._z;
	_t /= vec._t;
	return *this;
}

inline constexpr Vector4& Vector4::operator*=(const Real& real) {
	_x *= real;
	_y *= real;
	_z *= real;
	_t *= real;
	return *this;
}

inline constexpr Vector4& Vector4::operator/=(const Real& real) {
	#ifdef DEBUG
	if (real == 0) throw std::logic_error("Division by zero. Invalid real number");
	#endif

	_x /= real;
	_y /= real;
	_z /= real;
	_t /= real;
	return *this;
}

inline constexpr bool Vector4::operator>(const Vector4& vec) const {
	return dotself() > vec.dotself();
}

inline constexpr bool Vector4::operator<(const Vector4& vec) const {
	return dotself() < vec.dotself();
}

inline constexpr bool Vector4::operator>=(const Vector4& vec) const {
	return dotself() >= vec.dotself();
}

inline constexpr bool Vector4::operator<=(const Vector4& vec) const {
	return dotself() <= vec.dotself();
}

inline constexpr bool Vector4::operator==(const Vector4& vec) const {
	return _x == vec._x && _y == vec._y && _z == vec._z && _t == vec._t;
}

} // math namespace

