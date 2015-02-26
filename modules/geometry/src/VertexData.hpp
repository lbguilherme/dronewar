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

	VertexData(math::Vector3 point) : _point(point) {}

public:

	math::Vector3 _point;
	std::set<Edge> _edges;
	std::set<Triangle> _triangles;

};

}
