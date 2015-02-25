#include <gtest/gtest.h>

#include <geometry/Mesh>
#include <geometry/Vertex>
#include <geometry/Triangle>

using geometry::Mesh;
using geometry::Vertex;
using geometry::Triangle;

TEST(Triangle, Area) {
	Mesh mesh;
	
	Vertex v1 = mesh.addVertex({0, 0, 0});
	Vertex v2 = mesh.addVertex({1, 1, 0});
	Vertex v3 = mesh.addVertex({2, 0, 0});
	
	Triangle triangle = mesh.addTriangle(v1, v2, v3);
	
	EXPECT_DOUBLE_EQ(1, triangle.area());
}
