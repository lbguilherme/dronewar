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
	//Mesh(const Mesh&) = delete;
	//Mesh(Mesh&&) = delete;
	~Mesh();

	Vertex addVertex(math::Vector point);
	const std::set<Vertex>& vertices() const;

	Edge addEdge(Vertex v1, Vertex v2);
	const std::set<Edge>& edges() const;

	Triangle addTriangle(Edge e1, Edge e2, Edge e3);
	const std::set<Triangle>& triangles() const;

private:

	std::set<Vertex> _vertices;
	std::set<Edge> _edges;
	std::set<Triangle> _triangles;
	
};

}

