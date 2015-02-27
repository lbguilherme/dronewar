#include <gtest/gtest.h>
#include <sstream>

#include <math/Real>
#include <math/cte>
#include <geometry/Mesh>
#include <geometry/Solid>
#include <geometry/Vertex>
#include <geometry/Edge>
#include <geometry/Triangle>
#include <geometry/Transform>

using namespace math;
using namespace geometry;

TEST(Mesh, BuildCube) {
	Mesh cube;

	// Cube Vertices
	Vertex v1 = cube.addVertex({0, 0, 0});
	Vertex v2 = cube.addVertex({0, 0, 1});
	Vertex v3 = cube.addVertex({0, 1, 1});
	Vertex v4 = cube.addVertex({0, 1, 0});
	Vertex v5 = cube.addVertex({1, 0, 0});
	Vertex v6 = cube.addVertex({1, 0, 1});
	Vertex v7 = cube.addVertex({1, 1, 1});
	Vertex v8 = cube.addVertex({1, 1, 0});

	// Base
	Edge e12 = cube.addEdge(v1, v2);
	Edge e23 = cube.addEdge(v2, v3);
	Edge e34 = cube.addEdge(v3, v4);
	Edge e14 = cube.addEdge(v1, v4);
	Edge e13 = cube.addEdge(v1, v3);

	// Top
	Edge e56 = cube.addEdge(v5, v6);
	Edge e67 = cube.addEdge(v6, v7);
	Edge e78 = cube.addEdge(v7, v8);
	Edge e58 = cube.addEdge(v5, v8);
	Edge e57 = cube.addEdge(v5, v7);

	// Vertical Sides
	Edge e15 = cube.addEdge(v1, v5);
	Edge e26 = cube.addEdge(v2, v6);
	Edge e37 = cube.addEdge(v3, v7);
	Edge e48 = cube.addEdge(v4, v8);

	// Cross Sides
	Edge e16 = cube.addEdge(v1, v6);
	Edge e27 = cube.addEdge(v2, v7);
	Edge e38 = cube.addEdge(v3, v8);
	Edge e45 = cube.addEdge(v4, v5);

	// Bottom
	cube.addTriangle(e12, e23, e13);
	cube.addTriangle(e13, e34, e14);
	// Top
	cube.addTriangle(e56, e67, e57);
	cube.addTriangle(e57, e78, e58);
	// Right
	cube.addTriangle(e12, e26, e16);
	cube.addTriangle(e56, e15, e16);
	// Left
	cube.addTriangle(e34, e48, e38);
	cube.addTriangle(e78, e37, e38);
	// Front
	cube.addTriangle(v2, v3, v7);
	cube.addTriangle(e67, e26, e27);
	// Back
	cube.addTriangle(e14, e15, e45);
	cube.addTriangle(v5, v8, v4);

	// Duplicated (shall be ignored)
	cube.addEdge(v1, v4);
	cube.addEdge(v2, v7);
	cube.addEdge(v2, v7);
	cube.addEdge(v7, v2);
	cube.addEdge(v5, v8);
	cube.addTriangle(e15, e45, e14);
	cube.addTriangle(e58, e45, e48);
	cube.addTriangle(v1, v4, v5);

	EXPECT_EQ(8u, cube.vertices().size());
	EXPECT_EQ(18u, cube.edges().size());
	EXPECT_EQ(12u, cube.triangles().size());

	for (Edge e : cube.edges())
		EXPECT_EQ(2u, e.vertices().size());

	EXPECT_EQ(5u, v1.edges().size());
	EXPECT_EQ(4u, v2.edges().size());
	EXPECT_EQ(5u, v3.edges().size());
	EXPECT_EQ(4u, v4.edges().size());
	EXPECT_EQ(5u, v5.edges().size());
	EXPECT_EQ(4u, v6.edges().size());
	EXPECT_EQ(5u, v7.edges().size());
	EXPECT_EQ(4u, v8.edges().size());

	EXPECT_EQ(5u, v1.triangles().size());
	EXPECT_EQ(4u, v2.triangles().size());
	EXPECT_EQ(5u, v3.triangles().size());
	EXPECT_EQ(4u, v4.triangles().size());
	EXPECT_EQ(5u, v5.triangles().size());
	EXPECT_EQ(4u, v6.triangles().size());
	EXPECT_EQ(5u, v7.triangles().size());
	EXPECT_EQ(4u, v8.triangles().size());

	for (Edge e : cube.edges()) {
		Real expected;
		if (e == e16 || e == e27 || e == e38 || e == e45 || e == e13 || e == e57)
			expected = sqrt(2);
		else
			expected = 1;

		EXPECT_DOUBLE_EQ(expected, e.length());
	}

	for (Triangle t : cube.triangles())
		EXPECT_DOUBLE_EQ(0.5, t.area());
}

TEST(Mesh, ReadWrite) {
	Solid cubeSolid = Solid::cube();
	
	Transform transform;
	transform.scale(5);
	cubeSolid.apply(transform);
	
	Mesh& cube = cubeSolid;

	std::stringstream data;
	cube.write(data);

	Mesh cube2 = Mesh::read(data);

	EXPECT_EQ(cube.vertices().size(), cube2.vertices().size());
	EXPECT_EQ(cube.edges().size(), cube2.edges().size());
	EXPECT_EQ(cube.triangles().size(), cube2.triangles().size());
}

TEST(Mesh, TransformUniformScale) {
	Solid cube = Solid::cube();
	
	Transform transform;
	transform.scale(2);
	cube.apply(transform);
	
	for (Edge e : cube.edges()) {
		bool right = false;
		if (e.length() == 2) right = true;
		if (e.length() == 2*sqrt(2)) right = true;
		
		EXPECT_TRUE(right) << e.length();
	}
}

TEST(Mesh, TransformRotation) {
	Solid cube = Solid::cube();
	
	Transform transform;
	transform.rotateZ(cte::tau / 8);
	transform.rotateY(cte::tau / 8);
	transform.rotateX(cte::tau / 8);
	transform.rotateY(cte::tau / 8);
	transform.rotateZ(cte::tau / 8);
	cube.apply(transform);
	
	for (Edge e : cube.edges()) {
		bool right = false;
		if (std::abs(e.length() - 1) < 1e-8) right = true;
		if (std::abs(e.length() - sqrt(2)) < 1e-8) right = true;
		
		EXPECT_TRUE(right) << e.length();
	}
}
