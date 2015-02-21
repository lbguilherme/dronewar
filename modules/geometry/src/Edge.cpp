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

Vector Edge::vector() const {
	return _data->_vertices[1].vector() - _data->_vertices[0].vector();
}

Real Edge::length() const {
	return vector().length();
}
