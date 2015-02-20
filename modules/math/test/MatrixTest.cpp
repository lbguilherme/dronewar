#include <gtest/gtest.h>
#include <math/Matrix>
using math::Matrix;

struct MatrixAlgebra : public ::testing::Test {
	Matrix identity = Matrix::eye();
	Matrix one = Matrix::ones();
	Matrix null = Matrix::zeros();
};

TEST_F(MatrixAlgebra, Zeros) {
	EXPECT_DOUBLE_EQ(0, null(0, 0));
	EXPECT_DOUBLE_EQ(0, null(0, 1));
	EXPECT_DOUBLE_EQ(0, null(0, 2));
	
	EXPECT_DOUBLE_EQ(0, null(1, 0));
	EXPECT_DOUBLE_EQ(0, null(1, 1));
	EXPECT_DOUBLE_EQ(0, null(1, 2));
	
	EXPECT_DOUBLE_EQ(0, null(2, 0));
	EXPECT_DOUBLE_EQ(0, null(2, 1));
	EXPECT_DOUBLE_EQ(0, null(2, 2));
}

TEST_F(MatrixAlgebra, Ones) {
	EXPECT_DOUBLE_EQ(1, one(0, 0));
	EXPECT_DOUBLE_EQ(1, one(0, 1));
	EXPECT_DOUBLE_EQ(1, one(0, 2));
	
	EXPECT_DOUBLE_EQ(1, one(1, 0));
	EXPECT_DOUBLE_EQ(1, one(1, 1));
	EXPECT_DOUBLE_EQ(1, one(1, 2));
	
	EXPECT_DOUBLE_EQ(1, one(2, 0));
	EXPECT_DOUBLE_EQ(1, one(2, 1));
	EXPECT_DOUBLE_EQ(1, one(2, 2));
}

TEST_F(MatrixAlgebra, Identity) {
	EXPECT_DOUBLE_EQ(1, identity(0, 0));
	EXPECT_DOUBLE_EQ(0, identity(0, 1));
	EXPECT_DOUBLE_EQ(0, identity(0, 2));
	
	EXPECT_DOUBLE_EQ(0, identity(1, 0));
	EXPECT_DOUBLE_EQ(1, identity(1, 1));
	EXPECT_DOUBLE_EQ(0, identity(1, 2));
	
	EXPECT_DOUBLE_EQ(0, identity(2, 0));
	EXPECT_DOUBLE_EQ(0, identity(2, 1));
	EXPECT_DOUBLE_EQ(1, identity(2, 2));
}

TEST_F(MatrixAlgebra, Sum) {
	Matrix mat = identity + one;

	EXPECT_DOUBLE_EQ(2, mat(0, 0));
	EXPECT_DOUBLE_EQ(1, mat(0, 1));
	EXPECT_DOUBLE_EQ(1, mat(0, 2));
	
	EXPECT_DOUBLE_EQ(1, mat(1, 0));
	EXPECT_DOUBLE_EQ(2, mat(1, 1));
	EXPECT_DOUBLE_EQ(1, mat(1, 2));
	
	EXPECT_DOUBLE_EQ(1, mat(2, 0));
	EXPECT_DOUBLE_EQ(1, mat(2, 1));
	EXPECT_DOUBLE_EQ(2, mat(2, 2));
}

TEST_F(MatrixAlgebra, Multiplication) {
	Matrix mat = identity * one;
	EXPECT_DOUBLE_EQ(1, mat(0, 0));
	EXPECT_DOUBLE_EQ(1, mat(0, 1));
	EXPECT_DOUBLE_EQ(1, mat(0, 2));
	
	EXPECT_DOUBLE_EQ(1, mat(1, 0));
	EXPECT_DOUBLE_EQ(1, mat(1, 1));
	EXPECT_DOUBLE_EQ(1, mat(1, 2));
	
	EXPECT_DOUBLE_EQ(1, mat(2, 0));
	EXPECT_DOUBLE_EQ(1, mat(2, 1));
	EXPECT_DOUBLE_EQ(1, mat(2, 2));
	
	
	mat = 2 * identity * one;
	EXPECT_DOUBLE_EQ(2, mat(0, 0));
	EXPECT_DOUBLE_EQ(2, mat(0, 1));
	EXPECT_DOUBLE_EQ(2, mat(0, 2));
	
	EXPECT_DOUBLE_EQ(2, mat(1, 0));
	EXPECT_DOUBLE_EQ(2, mat(1, 1));
	EXPECT_DOUBLE_EQ(2, mat(1, 2));
	
	EXPECT_DOUBLE_EQ(2, mat(2, 0));
	EXPECT_DOUBLE_EQ(2, mat(2, 1));
	EXPECT_DOUBLE_EQ(2, mat(2, 2));
	
	mat *= one / 6;
	EXPECT_DOUBLE_EQ(1, mat(0, 0));
	EXPECT_DOUBLE_EQ(1, mat(0, 1));
	EXPECT_DOUBLE_EQ(1, mat(0, 2));
	
	EXPECT_DOUBLE_EQ(1, mat(1, 0));
	EXPECT_DOUBLE_EQ(1, mat(1, 1));
	EXPECT_DOUBLE_EQ(1, mat(1, 2));
	
	EXPECT_DOUBLE_EQ(1, mat(2, 0));
	EXPECT_DOUBLE_EQ(1, mat(2, 1));
	EXPECT_DOUBLE_EQ(1, mat(2, 2));
}
