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
	Real a = _data->_edges[0].length();
	Real b = _data->_edges[1].length();
	Real c = _data->_edges[2].length();
	Real p = (a+b+c)/2;
	return sqrt(p * (p-a) * (p-b) * (p-c));
}

Vector Triangle::normal() const {
	Vector a = _data->_edges[0].vector();
	Vector b = _data->_edges[1].vector();
	return (b.cross(a)).unit();
}

Vector Triangle::vector() const {
	return 1.0/3.0 * (_data->_edges[0].vector() + _data->_edges[1].vector() + _data->_edges[2].vector());
}

void Triangle::changeOrientation() {
	std::swap( _data->_edges[0], _data->_edges[1]);
}
