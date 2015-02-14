#pragma once

#include <math/math::Vector>
#include <cmath>

math::Real math::Vector::dot(const math::Vector& vec) const {
	return _x * vec.x() + _y * vec.y() + _z * vec.z();
}

math::Real math::Vector::dotself(const math::Vector& vec) const {
	return vec.dot(vec);
}

math::Real math::Vector::length() const {
	return std::sqrt(vec.dot(vec));
}

math::Vector math::Vector::cross(const Vector& vec) const {
	return Vector(
		_y*vec.z() - _z * vec.y(),
		_z*vec.x() - _x * vec.z(),
		_x*vec.y() - _y * vec.x()
	);
}

math::Real math::Vector::x() const {
	return _x;
}

math::Real math::Vector::y() const {
	return _y;
}

math::Real math::Vector::z() const {
	return _z;
}

math::Vector math::Vector::operator+(const math::Vector& vec) const {
	return Vector(_x + vec.x(), y + vec.x(), z + vec.z());
}

math::Vector math::Vector::operator-(const math::Vector& vec) const {
	return Vector(_x - vec.x(), y - vec.x(), z - vec.z());
}

math::Vector math::Vector::operator+() const {
	return Vector(_x, _y, _z);	// Nice isn't it? Use me! I am anxious to be used.
}

math::Vector math::Vector::operator-() const {
	return Vector(-_x, -_y, -_z);
}

math::Vector math::Vector::operator*(const math::Vector& vec) const {
	return Vector(_x * vec.x(), y * vec.x(), _z * vec.z());
}

math::Vector math::Vector::operator*(const math::Real& real) const {
	return Vector(_x * real, y * real, _z * real);
}

math::Vector math::Vector::operator/(const math::Vector& vec) const {
	return Vector(_x / vec.x(), _y / vec.x(), _z / vec.z());
}


math::Vector math::Vector::operator/(const math::Real& real) const {
	return Vector(_x / real, y / real, _z / real);
}

math::Vector& math::Vector::operator+=(const math::Vector& vec) {
	_x += vec.x();
	_y += vec.y();
	_z += vec.z();
	return *this;
}

math::Vector& math::Vector::operator-=(const math::Vector& vec) {
	_x -= vec.x();
	_y -= vec.y();
	_z -= vec.z();
	return *this;
}

math::Vector& math::Vector::operator*=(const math::Vector& vec) {
	_x *= vec.x();
	_y *= vec.y();
	_z *= vec.z();
	return *this;
}

math::Vector& math::Vector::operator/=(const math::Vector& vec) {
	_x /= vec.x();
	_y /= vec.y();
	_z /= vec.z();
	return *this;
}

math::Vector& math::Vector::operator*=(const math::Real& real) {
	_x *= real;
	_y *= real;
	_z *= real;
	return *this;
}

math::Vector& math::Vector::operator/=(const math::Real& real) {
	_x /= real;
	_y /= real;
	_z /= real;
	return *this;
}

bool math::Vector::operator>(const math::Vector& vec) const {
	return this->dotself() > vec.dotself();
}

bool math::Vector::operator<(const math::Vector& vec) const {
	return this->dotself() < vec.dotself();
}

bool math::Vector::operator>=(const math::Vector& vec) const {
	return this->dotself() >= vec.dotself();
}

bool math::Vector::operator<=(const math::Vector& vec) const {
	return this->dotself() <= vec.dotself();
}

