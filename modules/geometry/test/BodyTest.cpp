#include <gtest/gtest.h>

#include <math/Real>
#include <math/Vector>
#include <geometry/Solid>
#include <geometry/Vertex>
#include <geometry/Edge>
#include <geometry/Triangle>

using math::Real;
using math::Vector;
using geometry::Solid;
using geometry::Vertex;
using geometry::Edge;
using geometry::Triangle;

TEST(Solid, BuildCube) {
	Solid cube;

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

	// Top
	cube.addTriangle(e12, e23, e13);
	cube.addTriangle(e13, e34, e14);
	// Bottom
	cube.addTriangle(e56, e67, e57);
	cube.addTriangle(e57, e78, e58);
	// Right
	cube.addTriangle(e12, e26, e16);
	cube.addTriangle(e56, e15, e16);
	// Left
	cube.addTriangle(e34, e48, e38);
	cube.addTriangle(e78, e37, e38);
	// Front
	cube.addTriangle(e23, e37, e27);
	cube.addTriangle(e67, e26, e27);
	// Back
	cube.addTriangle(e14, e15, e45);
	cube.addTriangle(e58, e48, e45);

	Vector center;
	for (Vertex v : cube.vertices())
		center += v.vector();
	center /= cube.vertices().size();

	EXPECT_DOUBLE_EQ(0.5, center.x());
	EXPECT_DOUBLE_EQ(0.5, center.y());
	EXPECT_DOUBLE_EQ(0.5, center.z());

	cube.orient();

	for (Triangle t : cube.triangles()) {
		Vector pointAway = t.vector() + t.normal();
		Real dist = (center - pointAway).length();
		EXPECT_GT(dist, 1) << pointAway.x() << " " << pointAway.y() << " " << pointAway.z();
	}

	EXPECT_DOUBLE_EQ(1, cube.volume());
}
