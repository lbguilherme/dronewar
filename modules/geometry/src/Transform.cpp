#include <geometry/Transform>
#include <math/Vector4>

using math::Matrix44;
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

Vector Transform::apply(const Vector& point) {
	Vector4 p(point, 1);
	Vector4 result = _transform * p;
	return result.vector3();
}

void Transform::clear() {
	_transform = Matrix44::eye();
}
