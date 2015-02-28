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

	/// \brief Measures the volume of the solid. Complexity: O(n)
	///
	/// It assumes the solid has been sucessfully oriented.
	/// If solid is not oriented and this function is called, its Undefined Behaviour.
	math::Real volume() const;
	
	/// Calculates the center of the solid
	math::Vector3 center() const;
	
	/// Centralizes the Solid. Ie, its center will be at origin
	void centralize();
	
	/// \brief Produces a unit cube
	///
	/// Unit cube: All edges sizes of all cube faces equals to 1
	static Solid cube();
	
	/// \brief Produces a unit pyramid
	///
	/// Unit pyramid: The base perimeter equals 1, and the height equals 1.
	static Solid cone(unsigned sides);
};


} // namespace geometry
