#pragma once

#include <math/Real>
#include <math/Matrix>
#include <math/Vector>

namespace geometry {

class Transform {
	math::Matrix4 _transform;

public:

	Transform();
	
	/// Peform a uniform scaling
	void scale(math::Real scale);
	
	/// Peform a non-uniform scaling
	void scale(const math::Vector3& scale);
	
	/// Peform a translation
	void translate(const math::Vector3& translate);
	
	/// Rotation arround X axis. Angle in rads.
	void rotateX(const math::Real& angle);
	
	/// Rotation arround Y axis. Angle in rads.
	void rotateY(const math::Real& angle);
	
	/// Rotation arround Z axis. Angle in rads.
	void rotateZ(const math::Real& angle);
	
	/// Clear all transformations stored
	void clear();
	
	/// Application of the transformation in a point
	math::Vector3 apply(const math::Vector3& point) const;
};

} // geometry namespace
