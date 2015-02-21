#include <geometry/Triangle>
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
