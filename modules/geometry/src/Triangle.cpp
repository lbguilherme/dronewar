#include <geometry/Triangle>
#include <geometry/Edge>
#include <geometry/Mesh>
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