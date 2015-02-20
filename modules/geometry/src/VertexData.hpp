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

	VertexData(Mesh& mesh, math::Vector point) : _mesh(mesh) , _point(point) {}

public:

	Mesh& _mesh;
	math::Vector _point;
	std::set<Edge> _edges;
	std::set<Triangle> _triangles;

};

}
