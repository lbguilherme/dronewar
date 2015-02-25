#include <gtest/gtest.h>

#include <math/Real>
#include <math/Vector>
#include <geometry/Solid>
#include <geometry/Vertex>
#include <geometry/Edge>
#include <geometry/Triangle>

using math::Real;
using math::Vector;
using geometry::Mesh;
using geometry::Solid;
using geometry::Vertex;
using geometry::Edge;
using geometry::Triangle;


TEST(Triangle, Area) {
	Mesh mesh;
	
	Vertex v1 = mesh.addVertex({0, 0, 0});
	Vertex v2 = mesh.addVertex({1, 1, 0});
	Vertex v3 = mesh.addVertex({2, 0, 0});
	
	Edge e12 = mesh.addEdge(v1, v2);
	Edge e13 = mesh.addEdge(v1, v3);
	Edge e23 = mesh.addEdge(v2, v3);
	
	Triangle triangle = mesh.addTriangle(e12, e13, e23);
	
	EXPECT_DOUBLE_EQ(1, triangle.area());
}
