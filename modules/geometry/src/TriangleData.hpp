#pragma once

#include <array>

#include <geometry/Vertex>
#include <geometry/Edge>

namespace geometry {

class Mesh;

class TriangleData {
	friend class Mesh;
private:

	TriangleData(Edge e1, Edge e2, Edge e3, Vertex v1, Vertex v2, Vertex v3)
		: _vertices({{v1, v2, v3}}), _edges({{e1, e2, e3}}) {}

public:

	std::array<Vertex, 3> _vertices;
	std::array<Edge, 3> _edges;

};

}
