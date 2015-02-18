#pragma once

#include <math/Real>

namespace math {

class Matrix {
	Real _data[9];
	
public:
    constexpr Matrix();

	constexpr const Real& operator()(unsigned a, unsigned b) const;
	constexpr Real& operator()(unsigned a, unsigned b);
	
	constexpr const Real& operator()(unsigned a) const;
	constexpr Real& operator()(unsigned a);

	constexpr Matrix operator+(const Matrix& mat) const;
	constexpr Matrix operator-(const Matrix& mat) const;
	
	constexpr Matrix operator+() const;
	constexpr Matrix operator-() const;
	
	constexpr Matrix operator*(const Real& real) const;
	constexpr Matrix operator/(const Real& real) const;
	constexpr Matrix& operator*=(const Real& real);
	constexpr Matrix& operator/=(const Real& real);
	
	/// Matrix multiplication
	constexpr Matrix operator*(const Matrix& mat) const;
	
	/// Determinant of the matrix
	constexpr Real det() const;
	
	/// Transpost of the matrix
	constexpr Matrix transpost() const;
	
	/// Inverse of the matrix. Assumes matrix is inversible
	constexpr Matrix inverse() const;
};

constexpr Matrix::Matrix() : _data{0} {

}

constexpr const Real& Matrix::operator()(unsigned a, unsigned b) const {
	return _data[3*a+b];
}

constexpr Real& Matrix::operator()(unsigned a, unsigned b) {
	return _data[3*a+b];
}

constexpr const Real& Matrix::operator()(unsigned a) const {
	return _data[a];
}

constexpr Real& Matrix::operator()(unsigned a) {
	return _data[a];
}

constexpr Matrix Matrix::operator+(const Matrix& mat) const {
	Matrix result;
	for (int i = 0; i < 9; ++i) result._data[i] = _data[i] + mat(i);
	return result;
}	

constexpr Matrix Matrix::operator-(const Matrix& mat) const {
	Matrix result;
	for (int i = 0; i < 9; ++i) result._data[i] = _data[i] - mat(i);
	return result;
}

constexpr Matrix Matrix::operator+() const {
	return *this;
}

constexpr Matrix Matrix::operator-() const {
	Matrix result;
	for (int i = 0; i < 9; ++i) result._data[i] = -_data[i];
	return result;
}

constexpr Matrix Matrix::operator*(const Real& real) const {
	Matrix result;
	for (int i = 0; i < 9; ++i) result._data[i] = _data[i] * real;
	return result;
}

constexpr Matrix Matrix::operator/(const Real& real) const {
	Matrix result;
	for (int i = 0; i < 9; ++i) result._data[i] = _data[i] / real;
	return result;
}

constexpr Matrix& Matrix::operator*=(const Real& real) {
	for (int i = 0; i < 9; ++i) _data[i] *= real;
	return *this;
}

constexpr Matrix& Matrix::operator/=(const Real& real) {
	for (int i = 0; i < 9; ++i) _data[i] /= real;
	return *this;
}

constexpr Matrix Matrix::operator*(const Matrix& mat) const {
	Matrix result;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {
				result(i, j) = operator()(i, k) * mat(k, j);
			}
		}
	}
	return result;
}

constexpr Real Matrix::det() const {
    return + _data[0] * _data[4] * _data[8]
           + _data[1] * _data[5] * _data[6]
           + _data[2] * _data[3] * _data[7]
           - _data[2] * _data[4] * _data[6]
           - _data[1] * _data[3] * _data[8]
           - _data[0] * _data[5] * _data[7];
}

constexpr Matrix Matrix::transpost() const {
	Matrix result;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			result(i, j) = operator()(j, i);
		}
	}
	return result;
}

constexpr Matrix Matrix::inverse() const {
	Matrix result;
	result(0) = _data[4] * _data[8] - _data[7] * _data[5];
	result(1) = _data[2] * _data[7] - _data[8] * _data[1];
	result(2) = _data[1] * _data[5] - _data[4] * _data[2];
	result(3) = _data[5] * _data[6] - _data[8] * _data[3];
	result(4) = _data[0] * _data[8] - _data[6] * _data[2];
	result(5) = _data[2] * _data[3] - _data[5] * _data[0];
	result(6) = _data[3] * _data[7] - _data[6] * _data[4];
	result(7) = _data[1] * _data[6] - _data[7] * _data[0];
	result(8) = _data[0] * _data[1] - _data[3] * _data[4];
	return result / det();
}

}  // math namespace
