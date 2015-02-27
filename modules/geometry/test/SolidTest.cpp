#include <gtest/gtest.h>

#include <math/cte>
#include <math/Real>
#include <math/Vector>
#include <geometry/Solid>
#include <geometry/Vertex>
#include <geometry/Edge>
#include <geometry/Triangle>
#include <geometry/Transform>

using namespace math;
using namespace geometry;

TEST(Solid, OrientationUnitCube) {
	Solid cube = Solid::cube();
	
	Transform transform;
	transform.translate({0.5, 0.5, 0.5});
	cube.apply(transform);

	Vector3 center = cube.center();
	EXPECT_DOUBLE_EQ(0.5, center.x());
	EXPECT_DOUBLE_EQ(0.5, center.y());
	EXPECT_DOUBLE_EQ(0.5, center.z());

	cube.orient();

	for (Triangle t : cube.triangles()) {
		Vector3 pointAway = t.position() + t.normal();
		Real dist = (center - pointAway).length();
		EXPECT_GT(dist, 1);
	}

	EXPECT_DOUBLE_EQ(1, cube.volume());
}

TEST(Solid, OrientationUniformScaleCube) {
	Solid cube = Solid::cube();
	
	Transform transform;
	transform.scale(2);
	transform.translate({0.5, 0.5, 0.5});
	cube.apply(transform);

	Vector3 center = cube.center();
	EXPECT_DOUBLE_EQ(1, center.x());
	EXPECT_DOUBLE_EQ(1, center.y());
	EXPECT_DOUBLE_EQ(1, center.z());

	cube.orient();

	for (Triangle t : cube.triangles()) {
		Vector3 pointAway = t.position() + t.normal();
		Real dist = (center - pointAway).length();
		EXPECT_GT(dist, 1);
	}

	EXPECT_DOUBLE_EQ(8, cube.volume());
}

TEST(Solid, ShapeVolume) {
	Solid cube = Solid::cube();
	cube.orient();
	
	Transform transform;
	transform.scale({1, 2, 3});
	transform.rotateX(cte::tau / 8);
	transform.rotateZ(cte::tau / 8);
	cube.apply(transform);
	
	Vector3 center = cube.center();
	EXPECT_TRUE(std::abs(center.x()) < 1e-8) << center.x();
	EXPECT_TRUE(std::abs(center.y()) < 1e-8) << center.y();
	EXPECT_TRUE(std::abs(center.z()) < 1e-8) << center.z();
	
	for (Triangle t : cube.triangles()) {
		Vector3 pointAway = t.position() + t.normal();
		Real dist = (center - pointAway).length();
		EXPECT_GT(dist, 1);
	}
	
	EXPECT_DOUBLE_EQ(6, cube.volume());
}

TEST(Solid, ShapeOrientation) {
	Solid cube = Solid::cube();
	
	Transform transform;
	transform.scale({1, 2, 3});
	transform.rotateX(cte::tau / 8);
	transform.rotateZ(cte::tau / 8);
	cube.apply(transform);
	
	cube.orient();
	
	Vector3 center = cube.center();
	EXPECT_TRUE(std::abs(center.x()) < 1e-8) << center.x();
	EXPECT_TRUE(std::abs(center.y()) < 1e-8) << center.y();
	EXPECT_TRUE(std::abs(center.z()) < 1e-8) << center.z();
	
	for (Triangle t : cube.triangles()) {
		Vector3 pointAway = t.position() + t.normal();
		Real dist = (center - pointAway).length();
		EXPECT_GT(dist, 1);
	}
	
	EXPECT_DOUBLE_EQ(6, cube.volume());
}
