#include <math/Vector>
#include <cmath>

using namespace math;

Real Vector::dot(const Vector& vec) const {
	return _x * vec._x + _y * vec._y + _z * vec._z;
}

Real Vector::dotself() const {
	return dot(*this);
}

Real Vector::length() const {
	return std::sqrt(dot(*this));
}

Vector Vector::cross(const Vector& vec) const {
	return {
		_y*vec._z - _z * vec._y,
		_z*vec._x - _x * vec._z,
		_x*vec._y - _y * vec._x
	};
}

Real Vector::x() const {
	return _x;
}

Real Vector::y() const {
	return _y;
}

Real Vector::z() const {
	return _z;
}

Vector Vector::operator+(const Vector& vec) const {
	return {_x + vec._x, _y + vec._y, _z + vec._z};
}

Vector Vector::operator-(const Vector& vec) const {
	return {_x - vec._x, _y - vec._y, _z - vec._z};
}

Vector Vector::operator+() const {
	return {_x, _y, _z};	// Nice isn't it? Use me! I am anxious to be used.
}

Vector Vector::operator-() const {
	return {-_x, -_y, -_z};
}

Vector Vector::operator*(const Vector& vec) const {
	return {_x * vec._x, _y * vec._y, _z * vec._z};
}

Vector Vector::operator*(const Real& real) const {
	return {_x * real, _y * real, _z * real};
}

Vector Vector::operator/(const Vector& vec) const {
	return {_x / vec._x, _y / vec._x, _z / vec._z};
}


Vector Vector::operator/(const Real& real) const {
	return {_x / real, _y / real, _z / real};
}

Vector& Vector::operator+=(const Vector& vec) {
	_x += vec._x;
	_y += vec._y;
	_z += vec._z;
	return *this;
}

Vector& Vector::operator-=(const Vector& vec) {
	_x -= vec._x;
	_y -= vec._y;
	_z -= vec._z;
	return *this;
}

Vector& Vector::operator*=(const Vector& vec) {
	_x *= vec._x;
	_y *= vec._y;
	_z *= vec._z;
	return *this;
}

Vector& Vector::operator/=(const Vector& vec) {
	_x /= vec._x;
	_y /= vec._y;
	_z /= vec._z;
	return *this;
}

Vector& Vector::operator*=(const Real& real) {
	_x *= real;
	_y *= real;
	_z *= real;
	return *this;
}

Vector& Vector::operator/=(const Real& real) {
	_x /= real;
	_y /= real;
	_z /= real;
	return *this;
}

bool Vector::operator>(const Vector& vec) const {
	return dotself() > vec.dotself();
}

bool Vector::operator<(const Vector& vec) const {
	return dotself() < vec.dotself();
}

bool Vector::operator>=(const Vector& vec) const {
	return dotself() >= vec.dotself();
}

bool Vector::operator<=(const Vector& vec) const {
	return dotself() <= vec.dotself();
}

