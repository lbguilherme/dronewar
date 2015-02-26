#include <gtest/gtest.h>
#include <math/Matrix>
#include <math/Vector>

using math::Matrix3;
using math::Vector3;

struct MatrixAlgebra : public ::testing::Test {
	Matrix3 identity = Matrix3::eye();
	Matrix3 one = Matrix3::ones();
	Matrix3 null = Matrix3::zeros();
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

TEST_F(MatrixAlgebra, Multiplication) {
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

TEST_F(MatrixAlgebra, Determinant) {
	EXPECT_DOUBLE_EQ(1, identity.det());
	EXPECT_DOUBLE_EQ(8, (2*identity).det());
	EXPECT_DOUBLE_EQ(0, one.det());
	EXPECT_DOUBLE_EQ(0, (3*one).det());
	EXPECT_DOUBLE_EQ(0, null.det());
}

TEST_F(MatrixAlgebra, Inverse) {
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
