#include <gtest/gtest.h>
#include <math/Matrix>
#include <math/Vector>
#include <iostream>

using namespace math;

struct MatrixAlgebra3 : public ::testing::Test {
	Matrix3 identity = Matrix3::eye();
	Matrix3 one = Matrix3::ones();
	Matrix3 null = Matrix3::zeros();
};

TEST_F(MatrixAlgebra3, Zeros) {
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

TEST_F(MatrixAlgebra3, Ones) {
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

TEST_F(MatrixAlgebra3, Identity) {
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

TEST_F(MatrixAlgebra3, Sum) {
	Matrix3 mat = identity + one;

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

TEST_F(MatrixAlgebra3, Multiplication) {
	Matrix3 mat = identity * one;
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

TEST_F(MatrixAlgebra3, Determinant) {
	EXPECT_DOUBLE_EQ(1, identity.det());
	EXPECT_DOUBLE_EQ(8, (2*identity).det());
	EXPECT_DOUBLE_EQ(0, one.det());
	EXPECT_DOUBLE_EQ(0, (3*one).det());
	EXPECT_DOUBLE_EQ(0, null.det());
}

TEST_F(MatrixAlgebra3, Inverse) {
	Matrix3 idiv = identity.inverse();
	EXPECT_DOUBLE_EQ(1, idiv(0, 0));
	EXPECT_DOUBLE_EQ(0, idiv(0, 1));
	EXPECT_DOUBLE_EQ(0, idiv(0, 2));
	
	EXPECT_DOUBLE_EQ(0, idiv(1, 0));
	EXPECT_DOUBLE_EQ(1, idiv(1, 1));
	EXPECT_DOUBLE_EQ(0, idiv(1, 2));
	
	EXPECT_DOUBLE_EQ(0, idiv(2, 0));
	EXPECT_DOUBLE_EQ(0, idiv(2, 1));
	EXPECT_DOUBLE_EQ(1, idiv(2, 2));
	
	Matrix3 other = {1, 1, 1,   1, 2, 2,   2, 2, 1};
	idiv = other.inverse();
	EXPECT_DOUBLE_EQ(2, idiv(0, 0));
	EXPECT_DOUBLE_EQ(-1, idiv(0, 1));
	EXPECT_DOUBLE_EQ(0, idiv(0, 2));
	
	EXPECT_DOUBLE_EQ(-3, idiv(1, 0));
	EXPECT_DOUBLE_EQ(1, idiv(1, 1));
	EXPECT_DOUBLE_EQ(1, idiv(1, 2));
	
	EXPECT_DOUBLE_EQ(2, idiv(2, 0));
	EXPECT_DOUBLE_EQ(0, idiv(2, 1));
	EXPECT_DOUBLE_EQ(-1, idiv(2, 2));
}

TEST(MatrixAlgebra, Multiplication) {
	Matrix<10, 8> mat = 2 * Matrix<10, 5>::ones() * Matrix<5, 8>::ones();
	
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 8; ++j) {
			EXPECT_DOUBLE_EQ(10, mat(i, j));
		}
	}
}


struct MatrixVector : public ::testing::Test {
	Matrix3 identity = Matrix3::eye();
	Matrix3 one = Matrix3::ones();
	
	Vector3 i = {1, 0, 0};
	Vector3 j = {0, 1, 0};
	Vector3 k = {0, 0, 1};
};

TEST_F(MatrixVector, Construction) {
	Matrix3 tobuild(i, j, k);
	
	EXPECT_DOUBLE_EQ(1, tobuild(0, 0));
	EXPECT_DOUBLE_EQ(0, tobuild(0, 1));
	EXPECT_DOUBLE_EQ(0, tobuild(0, 2));
	
	EXPECT_DOUBLE_EQ(0, tobuild(1, 0));
	EXPECT_DOUBLE_EQ(1, tobuild(1, 1));
	EXPECT_DOUBLE_EQ(0, tobuild(1, 2));
	
	EXPECT_DOUBLE_EQ(0, tobuild(2, 0));
	EXPECT_DOUBLE_EQ(0, tobuild(2, 1));
	EXPECT_DOUBLE_EQ(1, tobuild(2, 2));
}

TEST_F(MatrixVector, Multiplication) {
	Vector3 test;
	
	test = 2 * one * i;
	EXPECT_DOUBLE_EQ(2, test(0));
	EXPECT_DOUBLE_EQ(2, test(1));
	EXPECT_DOUBLE_EQ(2, test(2));
	
	test = 3 * identity * i;
	EXPECT_DOUBLE_EQ(3, test(0));
	EXPECT_DOUBLE_EQ(0, test(1));
	EXPECT_DOUBLE_EQ(0, test(2));
	
	test = identity * j;
	EXPECT_DOUBLE_EQ(0, test(0));
	EXPECT_DOUBLE_EQ(1, test(1));
	EXPECT_DOUBLE_EQ(0, test(2));
	
	test = identity * k;
	EXPECT_DOUBLE_EQ(0, test(0));
	EXPECT_DOUBLE_EQ(0, test(1));
	EXPECT_DOUBLE_EQ(1, test(2));
}
