#include <gtest/gtest.h>

#include <math/Real>
#include <math/Vector>
#include <geometry/Solid>
#include <geometry/Vertex>
#include <geometry/Edge>
#include <geometry/Triangle>
#include <geometry/Transform>

using math::Real;
using math::Vector3;
using geometry::Solid;
using geometry::Vertex;
using geometry::Edge;
using geometry::Triangle;
using geometry::Transform;

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
