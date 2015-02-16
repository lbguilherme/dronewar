#pragma once

#include <math/Vector>
#include <cmath>
using namespace math;

Real Vector::dot(const Vector& vec) const {
	return _x * vec.x() + _y * vec.y() + _z * vec.z();
}

Real Vector::dotself() const {
	return dot(*this);
}

Real Vector::length() const {
	return std::sqrt(dot(*this));
}

Vector Vector::cross(const Vector& vec) const {
	return Vector(
		_y*vec.z() - _z * vec.y(),
		_z*vec.x() - _x * vec.z(),
		_x*vec.y() - _y * vec.x()
	);
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
	return Vector(_x + vec.x(), y + vec.x(), z + vec.z());
}

Vector Vector::operator-(const Vector& vec) const {
	return Vector(_x - vec.x(), y - vec.x(), z - vec.z());
}

Vector Vector::operator+() const {
	return {_x, _y, _z};	// Nice isn't it? Use me! I am anxious to be used.
}

Vector Vector::operator-() const {
	return Vector(-_x, -_y, -_z);
}

Vector Vector::operator*(const Vector& vec) const {
	return Vector(_x * vec.x(), y * vec.x(), _z * vec.z());
}

Vector Vector::operator*(const Real& real) const {
	return Vector(_x * real, y * real, _z * real);
}

Vector Vector::operator/(const Vector& vec) const {
	return Vector(_x / vec.x(), _y / vec.x(), _z / vec.z());
}


Vector Vector::operator/(const Real& real) const {
	return Vector(_x / real, y / real, _z / real);
}

Vector& Vector::operator+=(const Vector& vec) {
	_x += vec.x();
	_y += vec.y();
	_z += vec.z();
	return *this;
}

Vector& Vector::operator-=(const Vector& vec) {
	_x -= vec.x();
	_y -= vec.y();
	_z -= vec.z();
	return *this;
}

Vector& Vector::operator*=(const Vector& vec) {
	_x *= vec.x();
	_y *= vec.y();
	_z *= vec.z();
	return *this;
}

Vector& Vector::operator/=(const Vector& vec) {
	_x /= vec.x();
	_y /= vec.y();
	_z /= vec.z();
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

