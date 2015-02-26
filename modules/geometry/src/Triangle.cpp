#include <geometry/Triangle>
#include <geometry/Edge>
#include <geometry/Mesh>
#include <utility>
#include "TriangleData.hpp"

using namespace math;
using namespace geometry;

Triangle::Triangle(TriangleData* data) : _data(data) {

}

const std::array<Vertex, 3>& Triangle::vertices() const {
	return _data->_vertices;
}

const std::array<Edge, 3>& Triangle::edges() const {
	return _data->_edges;
}

Real Triangle::area() const {
	Vector3 a = _data->_edges[0].vector();
	Vector3 b = _data->_edges[1].vector();
	return 1.0 / 2.0 * (b.cross(a)).length();
}

Vector3 Triangle::vectorArea() const {
	Vector3 a = _data->_edges[0].vector();
	Vector3 b = _data->_edges[1].vector();
	return 1.0 / 2.0 * b.cross(a);
}

Vector3 Triangle::normal() const {
	Vector3 a = _data->_edges[0].vector();
	Vector3 b = _data->_edges[1].vector();
	return (b.cross(a)).unit();
}

Vector3 Triangle::position() const {
	return 1.0/3.0 * (_data->_vertices[0].position() + _data->_vertices[1].position() + _data->_vertices[2].position());
}

void Triangle::changeOrientation() {
	std::swap( _data->_edges[0], _data->_edges[1]);
}
