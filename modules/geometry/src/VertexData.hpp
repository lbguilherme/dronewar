#pragma once

#include <set>

#include <math/Vector>
#include <geometry/Triangle>

namespace geometry {

class Mesh;
class Edge;

class VertexData {
	friend class Mesh;
private:

	VertexData(math::Vector point) : _point(point) {}

public:

	math::Vector _point;
	std::set<Edge> _edges;
	std::set<Triangle> _triangles;

};

}
