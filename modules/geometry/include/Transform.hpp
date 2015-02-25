#pragma once

#include <math/Real>
#include <math/Matrix44>
#include <math/Vector>

namespace geometry {

class Transform {
	math::Matrix44 _transform;

public:

	Transform();
	
	/// Peform a uniform scaling
	void scale(math::Real scale);
	
	/// Peform a non-uniform scaling
	void scale(const math::Vector& scale);
	
	/// Peform a translation
	void translate(const math::Vector& translate);
	
	/// Clear all transformations stored
	void clear();
	
	/// Application of the transformation in a point
	math::Vector apply(const math::Vector& point);
};

} // geometry namespace
