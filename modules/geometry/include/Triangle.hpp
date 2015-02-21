#pragma once

#include <array>
#include <set>

#include <math/Real>

namespace geometry {

class Mesh;
class TriangleData;
class Edge;
class Vertex;

class Triangle {
	friend class Mesh;

public:

	Triangle(TriangleData* data);
	bool operator<(const Triangle& other) const {return _data < other._data;}
	bool operator==(const Triangle& other) const {return _data == other._data;}

	const std::array<Vertex, 3>& vertices() const;
	const std::array<Edge, 3>& edges() const;

	math::Real area() const;

private:

	TriangleData* _data;

};

}