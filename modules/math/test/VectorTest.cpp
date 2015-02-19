#include <gtest/gtest.h>

#include <math/Vector>

using math::Vector;

TEST(Vector, LengthComputation) {
	Vector v = {3, 4, 0};
	EXPECT_DOUBLE_EQ(5, v.length());
	EXPECT_DOUBLE_EQ(5, (-v).length());
}

