#include <geometry/Edge>
#include <geometry/Mesh>
#include "EdgeData.hpp"


using namespace math;
using namespace geometry;

Edge::Edge(EdgeData* data) : _data(data) {

}

const std::array<Vertex, 2>& Edge::vertices() const {
	return _data->_vertices;
}

const std::set<Triangle>& Edge::triangles() const {
	return _data->_triangles;
}

