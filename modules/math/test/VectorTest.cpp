#include <gtest/gtest.h>
#include <math/Vector>

using math::Vector;

TEST(Vector, LengthComputation) {
	Vector v = {3, 4, 0};
	EXPECT_DOUBLE_EQ(5, v.length());
	EXPECT_DOUBLE_EQ(5, (-v).length());
}

struct VectorAlgebra : public ::testing::Test {
	Vector i = {1, 0, 0};
	Vector j = {0, 1, 0};
	Vector k = {0, 0, 1};
};

TEST_F(VectorAlgebra, Equality) {
	Vector a = 2*i - 3*j + 5*k;
	Vector b = a;

	EXPECT_DOUBLE_EQ(2, a.x());
	EXPECT_DOUBLE_EQ(-3, a.y());
	EXPECT_DOUBLE_EQ(5, a.z());

	EXPECT_DOUBLE_EQ(2, b.x());
	EXPECT_DOUBLE_EQ(-3, b.y());
	EXPECT_DOUBLE_EQ(5, b.z());
}

TEST_F(VectorAlgebra, Sum) {
	Vector a = 2*i - 3*j + 5*k;
	Vector b = a;
	Vector c = i+j-k;

	EXPECT_DOUBLE_EQ(0, (a-b).x());
	EXPECT_DOUBLE_EQ(0, (a-b).y());
	EXPECT_DOUBLE_EQ(0, (a-b).z());

	EXPECT_DOUBLE_EQ(4, (a+b).x());
	EXPECT_DOUBLE_EQ(-6, (a+b).y());
	EXPECT_DOUBLE_EQ(10, (a+b).z());

	EXPECT_DOUBLE_EQ(3, (a+c).x());
	EXPECT_DOUBLE_EQ(-2, (a+c).y());
	EXPECT_DOUBLE_EQ(4, (a+c).z());

	a += i+j+k;
	EXPECT_DOUBLE_EQ(1, (a-b).x());
	EXPECT_DOUBLE_EQ(1, (a-b).y());
	EXPECT_DOUBLE_EQ(1, (a-b).z());
}

TEST_F(VectorAlgebra, Multiply) {
	Vector a = 2*i - 3*j + 5*k;
	Vector b = a;
	Vector c = i+j-k;

	EXPECT_DOUBLE_EQ(4, (a*b).x());
	EXPECT_DOUBLE_EQ(9, (a*b).y());
	EXPECT_DOUBLE_EQ(25, (a*b).z());

	EXPECT_DOUBLE_EQ(1, (a/b).x());
	EXPECT_DOUBLE_EQ(1, (a/b).y());
	EXPECT_DOUBLE_EQ(1, (a/b).z());

	EXPECT_DOUBLE_EQ(2, (a*c).x());
	EXPECT_DOUBLE_EQ(-3, (a*c).y());
	EXPECT_DOUBLE_EQ(-5, (a*c).z());

	a *= c;
	EXPECT_DOUBLE_EQ(2, a.x());
	EXPECT_DOUBLE_EQ(-3, a.y());
	EXPECT_DOUBLE_EQ(-5, a.z());
}
