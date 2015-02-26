#pragma once

#include <array>
#include <set>

#include <math/Real>
#include <math/Vector>

namespace geometry {

class Mesh;
class EdgeData;
class Vertex;
class Triangle;

class Edge {
	friend class Mesh;

public:

	Edge(EdgeData* data);
	bool operator<(const Edge& other) const {return _data < other._data;}
	bool operator==(const Edge& other) const {return _data == other._data;}

	const std::array<Vertex, 2>& vertices() const;
	const std::set<Triangle>& triangles() const;

	/// Gets the vector reprenseting the Edge
	math::Vector3 vector() const;

	/// Gets the length of the Edge
	math::Real length() const;

private:

	EdgeData* _data;

};

}
