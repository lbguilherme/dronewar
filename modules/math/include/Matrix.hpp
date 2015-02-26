#pragma once

#include <math/Real>
#include <math/Vector>
#include <stdexcept>
#include <array>

namespace math {

template <unsigned M, unsigned N>
class Matrix {
	static_assert(N*M > 0, "Can't make a matrix with no cells");
public:

	constexpr Matrix();

	constexpr Matrix(const Matrix<M, N>& other);
	constexpr Matrix(Matrix<M, N>& other);

	template <typename... Args>
	constexpr Matrix(const Vector<N>& head, const Args&... tail);

	template <typename... Args>
	constexpr Matrix(const Real& head, const Args&... tail);

	constexpr const Real& operator()(unsigned i, unsigned j) const;
	constexpr Real& operator()(unsigned i, unsigned j);
	
	constexpr const Real& operator()(unsigned x) const;
	constexpr Real& operator()(unsigned x);

	constexpr Matrix<M, N> operator+(const Matrix<M, N>& mat) const;
	constexpr Matrix<M, N> operator-(const Matrix<M, N>& mat) const;
	
	constexpr Matrix<M, N> operator+() const;
	constexpr Matrix<M, N> operator-() const;
	
	constexpr Matrix<M, N> operator*(const Real& real) const;
	constexpr Matrix<M, N> operator/(const Real& real) const;
	constexpr Matrix<M, N>& operator*=(const Real& real);
	constexpr Matrix<M, N>& operator/=(const Real& real);
	
	/// Matrix multiplication
	template <unsigned K>
	constexpr Matrix<M, K> operator*(const Matrix<N, K>& mat) const;

	constexpr Matrix<N, N>& operator*=(const Matrix<N, N>& mat);
	
	/// Transpost of the matrix
	constexpr Matrix<M, N> transpost() const;
	
	/// Determinant of the matrix
	constexpr Real det() const;
	
	/// Inverse of the matrix. Assumes matrix is inversible
	constexpr Matrix<N, N> inverse() const;
	
	/// Returns a null matrix.
	constexpr static const Matrix<M, N> zeros();
	
	/// Returns a matrix filled with ones.
	constexpr static const Matrix<M, N> ones();
	
	/// Returns identity matrix.
	constexpr static const Matrix<M, N> eye();

private:

	std::array<std::array<Real, M>, N> _v;

};

using Matrix2 = Matrix<2, 2>;
using Matrix3 = Matrix<3, 3>;
using Matrix4 = Matrix<4, 4>;

template <unsigned M, unsigned N>
inline constexpr Matrix<M, N>::Matrix() {
	for (unsigned i = 0; i < M; ++i) {
		for (unsigned j = 0; j < N; ++j) {
			_v[i][j] = 0;
		}
	}

}

template <unsigned M, unsigned N>
inline constexpr Matrix<M, N>::Matrix(const Matrix<M, N>& other) : _v(other._v) {

}

template <unsigned M, unsigned N>
inline constexpr Matrix<M, N>::Matrix(Matrix<M, N>& other) : _v(other._v) {

}

template <unsigned M, unsigned N>
template <typename... Args>
inline constexpr Matrix<M, N>::Matrix(const Vector<N>& head, const Args&... tail) {
	Vector<N> vecs[] = {head, tail...};

	for (unsigned i = 0; i < M; ++i)
		for (unsigned j = 0; j < N; ++j)
			_v[i][j] = vecs[j](i);
}

template <unsigned M, unsigned N>
template <typename... Args>
inline constexpr Matrix<M, N>::Matrix(const Real& head, const Args&... tail) {
	Real reals[] = {head, tail...};

	for (unsigned i = 0; i < M; ++i)
		for (unsigned j = 0; j < N; ++j)
			_v[i][j] = reals[i*M+j];
}

template <unsigned M, unsigned N>
constexpr Matrix<M, N> operator*(const Real& real, const Matrix<M, N>& matrix) {
	return matrix * real;
}

template <unsigned M, unsigned N>
constexpr Vector<M> operator*(const Matrix<M, N>& mat, const Vector<M>& vec) {
	Vector<M> result;
	for (unsigned i = 0; i < M; ++i) {
		for (unsigned j = 0; j < N; ++j) {
			result(i) += mat(i, j) * vec(j);
		}
	}

	return result;
}

template <unsigned M, unsigned N>
inline constexpr const Real& Matrix<M, N>::operator()(unsigned i, unsigned j) const {
#ifdef DEBUG
	if (i >= N || j >= M) throw std::logic_error("Invalid index");
#endif
	
	return _v[i][j];
}

template <unsigned M, unsigned N>
inline constexpr Real& Matrix<M, N>::operator()(unsigned i, unsigned j) {
#ifdef DEBUG
	if (i >= N || j >= M) throw std::logic_error("Invalid index");
#endif

	return _v[i][j];
}

template <unsigned M, unsigned N>
inline constexpr const Real& Matrix<M, N>::operator()(unsigned x) const {
#ifdef DEBUG
	if (x >= N*M) throw std::logic_error("Invalid index");
#endif

	return _v[x%M][x/M];
}

template <unsigned M, unsigned N>
inline constexpr Real& Matrix<M, N>::operator()(unsigned x) {
#ifdef DEBUG
	if (x >= N*M) throw std::logic_error("Invalid index");
#endif

	return _v[x%M][x/M];
}

template <unsigned M, unsigned N>
inline constexpr Matrix<M, N> Matrix<M, N>::operator+(const Matrix<M, N>& mat) const {
	Matrix<M, N> result;
	for (unsigned i = 0; i < M; ++i) {
		for (unsigned j = 0; j < N; ++j) {
			result(i, j) += _v[i][j] + mat(i, j);
		}
	}
	return result;
}	

template <unsigned M, unsigned N>
inline constexpr Matrix<M, N> Matrix<M, N>::operator-(const Matrix<M, N>& mat) const {
	Matrix<M, N> result;
	for (unsigned i = 0; i < M; ++i) {
		for (unsigned j = 0; j < N; ++j) {
			result(i, j) += _v[i][j] - mat(i, j);
		}
	}
	return result;
}

template <unsigned M, unsigned N>
inline constexpr Matrix<M, N> Matrix<M, N>::operator+() const {
	return (*this);
}

template <unsigned M, unsigned N>
inline constexpr Matrix<M, N> Matrix<M, N>::operator-() const {
	return (*this) * (-1);
}

template <unsigned M, unsigned N>
inline constexpr Matrix<M, N> Matrix<M, N>::operator*(const Real& real) const {
	Matrix<M, N> result;
	for (unsigned i = 0; i < M; ++i) {
		for (unsigned j = 0; j < N; ++j) {
			result(i, j) += _v[i][j] * real;
		}
	}
	return result;
}

template <unsigned M, unsigned N>
inline constexpr Matrix<M, N> Matrix<M, N>::operator/(const Real& real) const {
#ifdef DEBUG
	if (real == 0)
		throw std::logic_error("Can't divide by zero");
#endif

	Matrix<M, N> result;
	for (unsigned i = 0; i < M; ++i) {
		for (unsigned j = 0; j < N; ++j) {
			result(i, j) += _v[i][j] / real;
		}
	}
	return result;
}

template <unsigned M, unsigned N>
inline constexpr Matrix<M, N>& Matrix<M, N>::operator*=(const Real& real) {
	return (*this) = (*this) * real;
}

template <unsigned M, unsigned N>
inline constexpr Matrix<M, N>& Matrix<M, N>::operator/=(const Real& real) {
	return (*this) = (*this) / real;
}

template <unsigned M, unsigned N>
template <unsigned K>
inline constexpr Matrix<M, K> Matrix<M, N>::operator*(const Matrix<N, K>& mat) const {
	Matrix<M, K> result;
	for (unsigned i = 0; i < M; ++i) {
		for (unsigned k = 0; k < K; ++k) {
			for (unsigned j = 0; j < N; ++j) {
				result(i, k) += _v[i][j] * mat(j, k);
			}
		}
	}
	return result;
}

template <unsigned M, unsigned N>
inline constexpr Matrix<N, N>& Matrix<M, N>::operator*=(const Matrix<N, N>& mat) {
	static_assert(N == M, "Matrix must be squared for operator*= to work");
	return (*this) = (*this) * mat;
}

template <unsigned M, unsigned N>
inline constexpr Matrix<M, N> Matrix<M, N>::transpost() const {
	Matrix<M, N> result;
	for (unsigned i = 0; i < M; ++i) {
		for (unsigned j = 0; j < N; ++j) {
			result(j, i) = _v[i][j];
		}
	}
	return result;
}

template <unsigned M, unsigned N>
inline constexpr Real Matrix<M, N>::det() const {
	throw "not implemented";
	return 0;
}

template <unsigned M, unsigned N>
inline constexpr Matrix<N, N> Matrix<M, N>::inverse() const {
	static_assert(N == M, "Matrix must be squared for inverse() to work");

	throw "not implemented";
	return {};
}

template <unsigned M, unsigned N>
inline constexpr const Matrix<M, N> Matrix<M, N>::zeros() {
	return Matrix();
}

template <unsigned M, unsigned N>
inline constexpr const Matrix<M, N> Matrix<M, N>::ones() {
	Matrix<M, N> result;
	for (unsigned i = 0; i < M; ++i) {
		for (unsigned j = 0; j < N; ++j) {
			result(j, i) = 1;
		}
	}
	return result;
}

template <unsigned M, unsigned N>
inline constexpr const Matrix<M, N> Matrix<M, N>::eye() {
	Matrix<M, N> result;
	for (unsigned x = 0; x < N*M; ++x)
		result(x) = (x % (M+1) ? 0 : 1);
	return result;
}

}  // math namespace
