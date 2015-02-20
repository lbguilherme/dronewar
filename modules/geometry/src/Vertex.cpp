#include <geometry/Vertex>
#include <geometry/Mesh>
#include "VertexData.hpp"

using namespace math;
using namespace geometry;

Vertex::Vertex(VertexData* data) : _data(data) {

}

math::Vector Vertex::point() {
	return _data->_point;
}

const math::Vector Vertex::point() const {
	return _data->_point;
}

const std::set<Edge> Vertex::edges() const {
	return _data->_edges;
}

const std::set<Triangle> Vertex::triangles() const {
	return _data->_triangles;
}
