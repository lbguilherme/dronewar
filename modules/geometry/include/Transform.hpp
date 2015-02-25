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
	
	/// Rotation arround X axis. Angle in rads.
	void rotateX(const math::Real& angle);
	
	/// Rotation arround Y axis. Angle in rads.
	void rotateY(const math::Real& angle);
	
	/// Rotation arround Z axis. Angle in rads.
	void rotateZ(const math::Real& angle);
	
	/// Clear all transformations stored
	void clear();
	
	/// Application of the transformation in a point
	math::Vector apply(const math::Vector& point);
};

} // geometry namespace
