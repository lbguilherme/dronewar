#pragma once

#include <geometry/Mesh>
#include <math/Real>

namespace geometry {

class Solid : public Mesh {
public:

	/// Orients the solid positevely. Complexity: O(n²)
	/*!
		n is the total number of triangles in the mesh
		It flips the normal vectors of the triangles such that all of them is positive oriented.
		A positive oriented solid has all normal vectors pointing outwards
	*/
	void orient();

	/// Measures the volume of the solid. Complexity: O(n)
	math::Real volume() const;
	
	/// Calculates the center of the solid
	math::Vector3 center() const;
	
	/// Centralizes the Solid. Ie, its center will be at origin
	void centralize();
	
	/// Produces a unit cube
	static Solid cube();
};


} // namespace geometry
