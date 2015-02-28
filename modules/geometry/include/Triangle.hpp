#pragma once

#include <array>
#include <set>

#include <math/Real>
#include <math/Vector>

namespace geometry {

class Mesh;
class TriangleData;
class Edge;
class Vertex;

class Triangle {
	friend class Mesh;

public:

	Triangle() : Triangle(0) {}
	Triangle(TriangleData* data);
	bool operator<(const Triangle& other) const {return _data < other._data;}
	bool operator==(const Triangle& other) const {return _data == other._data;}

	bool isNull() { return _data == nullptr; }

	const std::array<Vertex, 3>& vertices() const;
	const std::array<Edge, 3>& edges() const;

	/// Gets the area of the Triangle
	math::Real area() const;
	
	/// Gets the vector reprenseting the area of the triangle
	math::Vector3 vectorArea() const;
	
	/// Gets a unit normal vector of the triangle
	math::Vector3 normal() const;
	
	/// Gets the position of the triangle
	math::Vector3 position() const;
	
	/// Changes the sign of the orientation vectors
	void changeOrientation();

private:

	TriangleData* _data;

};

}
