#include <geometry/Edge>
#include <geometry/Mesh>
#include <geometry/Vertex>
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

Vector3 Edge::vector() const {
	return _data->_vertices[1].position() - _data->_vertices[0].position();
}

Real Edge::length() const {
	return vector().length();
}
