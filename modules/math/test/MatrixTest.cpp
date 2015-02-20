#include <gtest/gtest.h>
#include <math/Matrix>
using math::Matrix;

struct MatrixAlgebra : public ::testing::Test {
	Matrix identity = Matrix::eye();
	Matrix one = Matrix::ones();
	Matrix null = Matrix::zeros();
};

TEST_F(MatrixAlgebra, Zeros) {
	EXPECT_DOUBLE_EQ(0, null(1, 1));
	EXPECT_DOUBLE_EQ(0, null(1, 2));
	EXPECT_DOUBLE_EQ(0, null(1, 3));
	
	EXPECT_DOUBLE_EQ(0, null(2, 1));
	EXPECT_DOUBLE_EQ(0, null(2, 2));
	EXPECT_DOUBLE_EQ(0, null(2, 3));
	
	EXPECT_DOUBLE_EQ(0, null(3, 1));
	EXPECT_DOUBLE_EQ(0, null(3, 2));
	EXPECT_DOUBLE_EQ(0, null(3, 3));
}

TEST_F(MatrixAlgebra, Ones) {
	EXPECT_DOUBLE_EQ(1, one(1, 1));
	EXPECT_DOUBLE_EQ(1, one(1, 2));
	EXPECT_DOUBLE_EQ(1, one(1, 3));
	
	EXPECT_DOUBLE_EQ(1, one(2, 1));
	EXPECT_DOUBLE_EQ(1, one(2, 2));
	EXPECT_DOUBLE_EQ(1, one(2, 3));
	
	EXPECT_DOUBLE_EQ(1, one(3, 1));
	EXPECT_DOUBLE_EQ(1, one(3, 2));
	EXPECT_DOUBLE_EQ(1, one(3, 3));
}

TEST_F(MatrixAlgebra, Identity) {
	EXPECT_DOUBLE_EQ(1, identity(1, 1));
	EXPECT_DOUBLE_EQ(0, identity(1, 2));
	EXPECT_DOUBLE_EQ(0, identity(1, 3));
	
	EXPECT_DOUBLE_EQ(0, identity(2, 1));
	EXPECT_DOUBLE_EQ(1, identity(2, 2));
	EXPECT_DOUBLE_EQ(0, identity(2, 3));
	
	EXPECT_DOUBLE_EQ(0, identity(3, 1));
	EXPECT_DOUBLE_EQ(0, identity(3, 2));
	EXPECT_DOUBLE_EQ(1, identity(3, 3));
}

TEST_F(MatrixAlgebra, Equality) {
	Matrix mat = identity + one;

	EXPECT_DOUBLE_EQ(2, mat(1, 1));
	EXPECT_DOUBLE_EQ(1, mat(1, 2));
	EXPECT_DOUBLE_EQ(1, mat(1, 3));
	
	EXPECT_DOUBLE_EQ(1, mat(2, 1));
	EXPECT_DOUBLE_EQ(2, mat(2, 2));
	EXPECT_DOUBLE_EQ(1, mat(2, 3));
	
	EXPECT_DOUBLE_EQ(1, mat(3, 1));
	EXPECT_DOUBLE_EQ(1, mat(3, 2));
	EXPECT_DOUBLE_EQ(2, mat(3, 3));
}
