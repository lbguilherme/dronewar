#pragma once

#include <set>

namespace math {
class Vector;
}

namespace geometry {

class Mesh;
class VertexData;
class Edge;
class Triangle;

class Vertex {
	friend class Mesh;

public:

	Vertex(VertexData* data);
	bool operator<(const Vertex& other) const {return _data < other._data;}
	bool operator==(const Vertex& other) const {return _data == other._data;}

	math::Vector& point();
	const math::Vector& point() const;

	const std::set<Edge>& edges() const;
	const std::set<Triangle>& triangles() const;
	
private:

	VertexData* _data;
	
};

}

