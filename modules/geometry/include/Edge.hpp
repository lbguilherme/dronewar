#pragma once

#include <array>

#include <geometry/Vertex>

namespace geometry {

class Mesh;
class EdgeData;

class Edge {
	friend class Mesh;

public:

	Edge(EdgeData* data);
	bool operator<(const Edge& other) const {return _data < other._data;}
	bool operator==(const Edge& other) const {return _data == other._data;}

	const std::array<Vertex, 2> vertices() const;
	const std::set<Triangle> triangles() const;

private:

	EdgeData* _data;

};

}
