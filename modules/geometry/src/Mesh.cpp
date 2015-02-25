#include <stdexcept>

#include <geometry/Mesh>
#include <geometry/Vertex>
#include <geometry/Edge>
#include "VertexData.hpp"
#include "EdgeData.hpp"
#include "TriangleData.hpp"

using namespace geometry;

Mesh::Mesh() {
	
}

Mesh::Mesh(Mesh&& other) {
	_vertices = std::move(other._vertices);
	_edges = std::move(other._edges);
	_triangles = std::move(other._triangles);
}

Mesh::~Mesh() {
	for (Vertex v : _vertices)
		delete v._data;

	for (Edge e : _edges)
		delete e._data;

	for (Triangle t : _triangles)
		delete t._data;
}

Vertex Mesh::addVertex(math::Vector point) {
	VertexData* data = nullptr;
	try {
		Vertex vertex(data = new VertexData(point));
		_vertices.insert(vertex);
		return vertex;
	}
	catch (...) {
		if (data) {
			{
				auto it = _vertices.find(Vertex(data));
				if (it != _vertices.end())
					_vertices.erase(it);
			}

			delete data;
		}
		throw;
	}
}

const std::set<Vertex>& Mesh::vertices() const {
	return _vertices;
}

Edge Mesh::addEdge(Vertex v1, Vertex v2) {
	for (const Edge& e : v1.edges()) {
		if (e.vertices()[0] == v2 || e.vertices()[1] == v2)
			return e;
	}

	EdgeData* data = nullptr;
	try {
		Edge edge(data = new EdgeData(v1, v2));
		_edges.insert(edge);
		v1._data->_edges.insert(edge);
		v2._data->_edges.insert(edge);
		return edge;
	}
	catch (...) {
		if (data) {
			{
				auto it = _edges.find(Edge(data));
				if (it != _edges.end())
					_edges.erase(it);
			}
			{
				auto it = v1._data->_edges.find(Edge(data));
				if (it != v1._data->_edges.end())
					v1._data->_edges.erase(it);
			}
			{
				auto it = v2._data->_edges.find(Edge(data));
				if (it != v2._data->_edges.end())
					v2._data->_edges.erase(it);
			}

			delete data;
		}
		throw;
	}
}

const std::set<Edge>& Mesh::edges() const {
	return _edges;
}


Triangle Mesh::addTriangle(Edge e1, Edge e2, Edge e3) {
	for (const Triangle& t : e1.triangles()) {
		if (t.edges()[0] == e2 || t.edges()[1] == e2 || t.edges()[2] == e2)
			if (t.edges()[0] == e3 || t.edges()[1] == e3 || t.edges()[2] == e3)
				return t;
	}

	Vertex v1 = e1.vertices()[0];
	Vertex v2 = e1.vertices()[1];
	Vertex v3 = e2.vertices()[0] == e1.vertices()[0] || e2.vertices()[0] == e1.vertices()[1] ? e2.vertices()[1] : e2.vertices()[0];
	TriangleData* data = nullptr;
	try {
		Triangle triangle(data = new TriangleData(e1, e2, e3, v1, v2, v3));
		_triangles.insert(triangle);
		v1._data->_triangles.insert(triangle);
		v2._data->_triangles.insert(triangle);
		v3._data->_triangles.insert(triangle);
		e1._data->_triangles.insert(triangle);
		e2._data->_triangles.insert(triangle);
		e3._data->_triangles.insert(triangle);
		return triangle;
	} catch (...) {
		if (data) {
			{
				auto it = _triangles.find(Triangle(data));
				if (it != _triangles.end())
					_triangles.erase(it);
			}
			{
				auto it = v1._data->_triangles.find(Triangle(data));
				if (it != v1._data->_triangles.end())
					v1._data->_triangles.erase(it);
			}
			{
				auto it = v2._data->_triangles.find(Triangle(data));
				if (it != v2._data->_triangles.end())
					v2._data->_triangles.erase(it);
			}
			{
				auto it = v3._data->_triangles.find(Triangle(data));
				if (it != v3._data->_triangles.end())
					v3._data->_triangles.erase(it);
			}
			{
				auto it = e1._data->_triangles.find(Triangle(data));
				if (it != e1._data->_triangles.end())
					e1._data->_triangles.erase(it);
			}
			{
				auto it = e2._data->_triangles.find(Triangle(data));
				if (it != e2._data->_triangles.end())
					e2._data->_triangles.erase(it);
			}
			{
				auto it = e3._data->_triangles.find(Triangle(data));
				if (it != e3._data->_triangles.end())
					e3._data->_triangles.erase(it);
			}

			delete data;
		}
		throw;
	}
}

const std::set<Triangle>& Mesh::triangles() const {
	return _triangles;
}
