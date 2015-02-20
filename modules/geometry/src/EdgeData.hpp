#pragma once

#include <array>

#include <geometry/Vertex>
#include <geometry/Triangle>

namespace geometry {

class Mesh;

class EdgeData {
	friend class Mesh;
private:

	EdgeData(Mesh& mesh, Vertex v1, Vertex v2) : _mesh(mesh), _vertices({{v1, v2}}) {}

public:

	Mesh& _mesh;
	std::array<Vertex, 2> _vertices;
	std::set<Triangle> _triangles;

};

}
