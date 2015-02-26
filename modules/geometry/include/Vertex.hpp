#pragma once

#include <set>
#include <math/Vector>

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

	math::Vector3& position();
	const math::Vector3& position() const;

	const std::set<Edge>& edges() const;
	const std::set<Triangle>& triangles() const;
	
private:

	VertexData* _data;
	
};

}

