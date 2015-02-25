#include <gtest/gtest.h>

#include <math/Real>
#include <geometry/Mesh>
#include <geometry/Vertex>
#include <geometry/Edge>
#include <geometry/Triangle>
#include <geometry/Ray>
#include <geometry/RayHit>

using math::Real;
using geometry::Mesh;
using geometry::Vertex;
using geometry::Edge;
using geometry::Triangle;
using geometry::Ray;
using geometry::RayHit;
#include <iostream>
using namespace std;
TEST(RayCast, ComplexMesh) {
	Mesh mesh;

	Vertex v1 = mesh.addVertex({0, 0, 0});
	Vertex v2 = mesh.addVertex({1, 1, 0});
	Vertex v3 = mesh.addVertex({2, 0, 0});
	Vertex v4 = mesh.addVertex({3, 1, 0});
	Vertex v5 = mesh.addVertex({4, 0, 0});
	Vertex v6 = mesh.addVertex({2, 1, 3});
	Vertex v7 = mesh.addVertex({2.5, 0.5, 1});

	Edge e12 = mesh.addEdge(v1, v2);
	Edge e23 = mesh.addEdge(v2, v3);
	Edge e34 = mesh.addEdge(v3, v4);
	Edge e45 = mesh.addEdge(v4, v5);

	Edge e13 = mesh.addEdge(v1, v3);
	Edge e24 = mesh.addEdge(v2, v4);
	Edge e35 = mesh.addEdge(v3, v5);

	Edge e14 = mesh.addEdge(v1, v4);
	Edge e16 = mesh.addEdge(v1, v6);
	Edge e46 = mesh.addEdge(v4, v6);

	Edge e37 = mesh.addEdge(v3, v7);
	Edge e47 = mesh.addEdge(v4, v7);

	Triangle t123 = mesh.addTriangle(e12, e23, e13);
	Triangle t243 = mesh.addTriangle(e24, e34, e23);
	Triangle t345 = mesh.addTriangle(e45, e35, e34);
	Triangle t146 = mesh.addTriangle(e14, e16, e46);
	Triangle t347 = mesh.addTriangle(e34, e37, e47);

	Ray ray1({-1, 0.5, 0}, {1, 0, 0});
	Ray ray2({-1, 0.5, 0}, {1, 0, 0.2});
	Ray ray3({-1, 0.5, 0}, {1, 0, 1});
	Ray ray4({-2, 0, 0}, {1, 0, 0});
	Ray ray5({0, 0.5, 1}, {3.5, 0, -1});
	Ray ray6({0, 0.5, 1}, {2.5, 0, -1});

	EXPECT_FALSE(ray1.castOnTriangle(t123).hasHit());
	EXPECT_FALSE(ray1.castOnTriangle(t243).hasHit());
	EXPECT_FALSE(ray1.castOnTriangle(t345).hasHit());
	EXPECT_TRUE(ray1.castOnTriangle(t146).hasHit());
	EXPECT_TRUE(ray1.castOnTriangle(t347).hasHit());
	EXPECT_EQ(2u, ray1.castOnMesh(mesh).size());

	EXPECT_FALSE(ray2.castOnTriangle(t123).hasHit());
	EXPECT_FALSE(ray2.castOnTriangle(t243).hasHit());
	EXPECT_FALSE(ray2.castOnTriangle(t345).hasHit());
	EXPECT_TRUE(ray2.castOnTriangle(t146).hasHit());
	EXPECT_TRUE(ray2.castOnTriangle(t347).hasHit());
	EXPECT_EQ(2u, ray2.castOnMesh(mesh).size());

	EXPECT_FALSE(ray3.castOnTriangle(t123).hasHit());
	EXPECT_FALSE(ray3.castOnTriangle(t243).hasHit());
	EXPECT_FALSE(ray3.castOnTriangle(t345).hasHit());
	EXPECT_FALSE(ray3.castOnTriangle(t146).hasHit());
	EXPECT_EQ(0u, ray3.castOnMesh(mesh).size());

	EXPECT_FALSE(ray4.castOnTriangle(t123).hasHit());
	EXPECT_FALSE(ray4.castOnTriangle(t243).hasHit());
	EXPECT_FALSE(ray4.castOnTriangle(t345).hasHit());
	EXPECT_TRUE(ray4.castOnTriangle(t146).hasHit());
	EXPECT_TRUE(ray4.castOnTriangle(t347).hasHit());
	EXPECT_EQ(2u, ray4.castOnMesh(mesh).size());

	EXPECT_FALSE(ray5.castOnTriangle(t123).hasHit());
	EXPECT_FALSE(ray5.castOnTriangle(t243).hasHit());
	EXPECT_TRUE(ray5.castOnTriangle(t345).hasHit());
	EXPECT_TRUE(ray5.castOnTriangle(t146).hasHit());
	EXPECT_TRUE(ray5.castOnTriangle(t347).hasHit());
	EXPECT_EQ(3u, ray5.castOnMesh(mesh).size());

	EXPECT_FALSE(ray6.castOnTriangle(t123).hasHit());
	EXPECT_TRUE(ray6.castOnTriangle(t243).hasHit());
	EXPECT_TRUE(ray6.castOnTriangle(t345).hasHit());
	EXPECT_TRUE(ray6.castOnTriangle(t146).hasHit());
	EXPECT_TRUE(ray6.castOnTriangle(t347).hasHit());
	EXPECT_EQ(2u, ray6.castOnMesh(mesh).size());
}

TEST(RayCast, Triangles) {
	Mesh m;

	Vertex v1 = m.addVertex({0,   0, 0});
	Vertex v2 = m.addVertex({0.5, 1, 0});
	Vertex v3 = m.addVertex({1,   0, 0});

	Edge e12 = m.addEdge(v1, v2);
	Edge e23 = m.addEdge(v2, v3);
	Edge e13 = m.addEdge(v1, v3);

	Triangle t = m.addTriangle(e12, e23, e13);

	Ray ray{{0.5, 0.5, 1}, {0, 0, -1}};
	RayHit hit = ray.castOnTriangle(t);

	EXPECT_TRUE(hit.hasHit());

	EXPECT_DOUBLE_EQ(0.5, hit.point().x());
	EXPECT_DOUBLE_EQ(0.5, hit.point().y());
	EXPECT_DOUBLE_EQ(0, hit.point().z());

	auto hits = ray.castOnMesh(m);
	EXPECT_EQ(1u, hits.size());
	auto hit2 = *hits.begin();

	EXPECT_DOUBLE_EQ(0.5, hit2.point().x());
	EXPECT_DOUBLE_EQ(0.5, hit2.point().y());
	EXPECT_DOUBLE_EQ(0, hit2.point().z());
}
