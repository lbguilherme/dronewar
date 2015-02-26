#pragma once

#include <set>

#include <math/Vector>
#include <geometry/Vertex>
#include <geometry/Edge>
#include <geometry/Triangle>

namespace geometry {

class Mesh {
public:

	Mesh();
	Mesh(const Mesh&) = delete;
	Mesh(Mesh&& other);
	~Mesh();

	Vertex addVertex(math::Vector3 point);
	const std::set<Vertex>& vertices() const;

	Edge addEdge(Vertex v1, Vertex v2);
	const std::set<Edge>& edges() const;

	Triangle addTriangle(Vertex v1, Vertex v2, Vertex v3);
	Triangle addTriangle(Edge e1, Edge e2, Edge e3);
	const std::set<Triangle>& triangles() const;

	void write(std::ostream& out) const;
	static Mesh read(std::istream &in);

private:

	std::set<Vertex> _vertices;
	std::set<Edge> _edges;
	std::set<Triangle> _triangles;
	
};

}

