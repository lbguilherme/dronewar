#include <geometry/Transform>
#include <math/Vector4>
#include <cmath>

using math::Matrix44;
using math::Real;
using math::Vector;
using math::Vector4;
using geometry::Transform;

Transform::Transform() {
	clear();
}

void Transform::scale(math::Real scale) {
	Matrix44 sub = scale * Matrix44::eye();
	sub(15) = 1;
	_transform *= sub;
}

void Transform::scale(const Vector& scale) {
	Matrix44 sub = Matrix44::eye();
	for (int i = 0; i < 3; ++i) sub(5*i) = scale(i);
	_transform *= sub;
}

void Transform::translate(const math::Vector& translate) {
	Matrix44 sub = Matrix44::eye();
	for (int i = 0; i < 3; ++i) sub(5*i+3) = translate(i);
	_transform *= sub;
}

void Transform::rotateX(const math::Real& angle) {
	Matrix44 sub = Matrix44::eye();
	Real c = std::cos(angle);
	Real s = std::sin(angle);
	sub(5) = c; sub(6) = -s;
	sub(9) = s; sub(10) = c;
	
	_transform *= sub;
}

void Transform::rotateY(const math::Real& angle) {
	Matrix44 sub = Matrix44::eye();
	Real c = std::cos(angle);
	Real s = std::sin(angle);
	sub(0) = c; sub(2) = s;
	sub(8) = -s; sub(10) = c;
	
	_transform *= sub;
}

void Transform::rotateZ(const math::Real& angle) {
	Matrix44 sub = Matrix44::eye();
	Real c = std::cos(angle);
	Real s = std::sin(angle);
	sub(0) = c; sub(1) = -s;
	sub(4) = s; sub(5) = c;
	
	_transform *= sub;
}

Vector Transform::apply(const Vector& point) {
	Vector4 p(point, 1);
	Vector4 result = _transform * p;
	return result.vector3();
}

void Transform::clear() {
	_transform = Matrix44::eye();
}
