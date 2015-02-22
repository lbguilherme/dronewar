#pragma once

#include <math/Real>
#include <math/Vector>
#include <stdexcept>

namespace math {

class Matrix {
	Real _data[9];
	
public:
	constexpr Matrix();
	constexpr Matrix(const Vector& a, const Vector& b, const Vector& c);

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
	constexpr Matrix& operator*=(const Matrix& mat);
	
	/// Determinant of the matrix
	constexpr Real det() const;
	
	/// Transpost of the matrix
	constexpr Matrix transpost() const;
	
	/// Inverse of the matrix. Assumes matrix is inversible
	constexpr Matrix inverse() const;
	
	/// Returns a null matrix.
	constexpr static const Matrix zeros();
	
	/// Returns a matrix filled with ones.
	constexpr static const Matrix ones();
	
	/// Returns identity matrix.
	constexpr static const Matrix eye();
};

constexpr Matrix operator*(const Real& real, const Matrix& matrix);
constexpr Vector operator*(const Matrix& mat, const Vector& vec);

constexpr Matrix operator*(const Real& real, const Matrix& matrix) {
	return matrix * real;
}

constexpr Vector operator*(const Matrix& mat, const Vector& vec) {
	Vector result;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			result(i) += mat(i, j) * vec(j);
		}
	}
	
	return result;
}

inline constexpr Matrix::Matrix() : _data{0} {

}

inline constexpr Matrix::Matrix(const Vector& a, const Vector& b, const Vector& c) : 
	_data{
		a(0), b(0), c(0),
		a(1), b(1), c(1),
		a(2), b(2), c(2),
	} {}

inline constexpr const Real& Matrix::operator()(unsigned a, unsigned b) const {
	#ifdef DEBUG
	if (a >= 3 || b >= 3) throw std::logic_error("Invalid index");
	#endif
	
	return _data[3*a+b];
}

inline constexpr Real& Matrix::operator()(unsigned a, unsigned b) {
	#ifdef DEBUG
	if (a >= 3 || b >= 3) throw std::logic_error("Invalid index");
	#endif

	return _data[3*a+b];
}

inline constexpr const Real& Matrix::operator()(unsigned a) const {
	#ifdef DEBUG
	if (a > 9) throw std::logic_error("Invalid index");
	#endif

	return _data[a];
}

inline constexpr Real& Matrix::operator()(unsigned a) {
	#ifdef DEBUG
	if (a > 9) throw std::logic_error("Invalid index");
	#endif

	return _data[a];
}

inline constexpr Matrix Matrix::operator+(const Matrix& mat) const {
	Matrix result;
	for (int i = 0; i < 9; ++i) result._data[i] = _data[i] + mat(i);
	return result;
}	

inline constexpr Matrix Matrix::operator-(const Matrix& mat) const {
	Matrix result;
	for (int i = 0; i < 9; ++i) result._data[i] = _data[i] - mat(i);
	return result;
}

inline constexpr Matrix Matrix::operator+() const {
	return *this;
}

inline constexpr Matrix Matrix::operator-() const {
	Matrix result;
	for (int i = 0; i < 9; ++i) result._data[i] = -_data[i];
	return result;
}

inline constexpr Matrix Matrix::operator*(const Real& real) const {
	Matrix result;
	for (int i = 0; i < 9; ++i) result._data[i] = _data[i] * real;
	return result;
}

inline constexpr Matrix Matrix::operator/(const Real& real) const {
	Matrix result;
	for (int i = 0; i < 9; ++i) result._data[i] = _data[i] / real;
	return result;
}

inline constexpr Matrix& Matrix::operator*=(const Real& real) {
	for (int i = 0; i < 9; ++i) _data[i] *= real;
	return *this;
}

inline constexpr Matrix& Matrix::operator/=(const Real& real) {
	#ifdef DEBUG
	if (real == 0) throw std::logic_error("Can't divide by zero");
	#endif

	for (int i = 0; i < 9; ++i) _data[i] /= real;
	return *this;
}

inline constexpr Matrix Matrix::operator*(const Matrix& mat) const {
	Matrix result;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {
				result(i, j) += operator()(i, k) * mat(k, j);
			}
		}
	}
	return result;
}

inline constexpr Matrix& Matrix::operator*=(const Matrix& mat) {
	return (*this) = (*this) * mat;
}

inline constexpr Real Matrix::det() const {
	return
			+ _data[0] * _data[4] * _data[8]
			+ _data[1] * _data[5] * _data[6]
			+ _data[2] * _data[3] * _data[7]
			- _data[2] * _data[4] * _data[6]
			- _data[1] * _data[3] * _data[8]
			- _data[0] * _data[5] * _data[7];
}

inline constexpr Matrix Matrix::transpost() const {
	Matrix result;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			result(i, j) = operator()(j, i);
		}
	}
	return result;
}

inline constexpr Matrix Matrix::inverse() const {
	Real d = det();
	if (d == 0) throw std::logic_error("Matrix is non invertible");

	Matrix result;
	result(0) = _data[4] * _data[8] - _data[7] * _data[5];
	result(1) = _data[2] * _data[7] - _data[8] * _data[1];
	result(2) = _data[1] * _data[5] - _data[4] * _data[2];
	result(3) = _data[5] * _data[6] - _data[8] * _data[3];
	result(4) = _data[0] * _data[8] - _data[6] * _data[2];
	result(5) = _data[2] * _data[3] - _data[5] * _data[0];
	result(6) = _data[3] * _data[7] - _data[6] * _data[4];
	result(7) = _data[1] * _data[6] - _data[7] * _data[0];
	result(8) = _data[0] * _data[4] - _data[2] * _data[3];
	return result / d;
}

inline constexpr const Matrix Matrix::zeros() {
	return Matrix();
}

inline constexpr const Matrix Matrix::ones() {
	Matrix result;
	for (int i = 0; i < 9; ++i) result._data[i] = 1;
	return result;
}

inline constexpr const Matrix Matrix::eye() {
	Matrix result;
	for (int i = 0; i < 9; ++i) result._data[i] = (i % 4 ? 0 : 1);
	return result;
}

}  // math namespace
