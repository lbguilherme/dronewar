#pragma once

#include <math/Real>
#include <math/Vector>
#include <stdexcept>
#include <array>

namespace math {

template <unsigned N, unsigned M>
class Matrix {
	static_assert(N*M > 0, "Can't make a matrix with no cells");
public:

	constexpr Matrix();

	constexpr Matrix(const Matrix<N, M>& other);
	constexpr Matrix(Matrix<N, M>& other);

	template <typename... Args>
	constexpr Matrix(const Vector<N>& head, const Args&... tail);

	template <typename... Args>
	constexpr Matrix(const Real& head, const Args&... tail);

	constexpr const Real& operator()(unsigned i, unsigned j) const;
	constexpr Real& operator()(unsigned i, unsigned j);
	
	constexpr const Real& operator()(unsigned x) const;
	constexpr Real& operator()(unsigned x);

	constexpr Matrix<N, M> operator+(const Matrix<N, M>& mat) const;
	constexpr Matrix<N, M> operator-(const Matrix<N, M>& mat) const;
	
	constexpr Matrix<N, M> operator+() const;
	constexpr Matrix<N, M> operator-() const;
	
	constexpr Matrix<N, M> operator*(const Real& real) const;
	constexpr Matrix<N, M> operator/(const Real& real) const;
	constexpr Matrix<N, M>& operator*=(const Real& real);
	constexpr Matrix<N, M>& operator/=(const Real& real);
	
	/// Matrix multiplication
	template <unsigned K>
	constexpr Matrix<N, K> operator*(const Matrix<M, K>& mat) const;

	constexpr Matrix<N, N>& operator*=(const Matrix<N, N>& mat);
	
	/// Determinant of the matrix
	constexpr Real det() const;
	
	/// Transpost of the matrix
	constexpr Matrix<M, N> transpost() const;
	
	/// Inverse of the matrix. Assumes matrix is inversible
	constexpr Matrix<N, N> inverse() const;
	
	/// Returns a null matrix.
	constexpr static const Matrix<N, M> zeros();
	
	/// Returns a matrix filled with ones.
	constexpr static const Matrix<N, M> ones();
	
	/// Returns identity matrix.
	constexpr static const Matrix<N, M> eye();

private:

	std::array<std::array<Real, M>, N> _v;

};

using Matrix2 = Matrix<2, 2>;
using Matrix3 = Matrix<3, 3>;
using Matrix4 = Matrix<4, 4>;

template <unsigned N, unsigned M>
inline constexpr Matrix<N, M>::Matrix() {
	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < M; ++j) {
			_v[i][j] = 0;
		}
	}

}

template <unsigned N, unsigned M>
inline constexpr Matrix<N, M>::Matrix(const Matrix<N, M>& other) : _v(other._v) {

}

template <unsigned N, unsigned M>
inline constexpr Matrix<N, M>::Matrix(Matrix<N, M>& other) : _v(other._v) {

}

template <unsigned N, unsigned M>
template <typename... Args>
inline constexpr Matrix<N, M>::Matrix(const Vector<N>& head, const Args&... tail) {
	Vector<N> vecs[] = {head, tail...};

	for (unsigned i = 0; i < N; ++i)
		for (unsigned j = 0; j < M; ++j)
			_v[i][j] = vecs[j](i);
}

template <unsigned N, unsigned M>
template <typename... Args>
inline constexpr Matrix<N, M>::Matrix(const Real& head, const Args&... tail) {
	Real reals[] = {head, tail...};

	for (unsigned i = 0; i < N; ++i)
		for (unsigned j = 0; j < M; ++j)
			_v[i][j] = reals[i*M+j];
}

template <unsigned N, unsigned M>
constexpr Matrix<N, M> operator*(const Real& real, const Matrix<N, M>& matrix) {
	return matrix * real;
}

template <unsigned N, unsigned M>
constexpr Vector<M> operator*(const Matrix<N, M>& mat, const Vector<M>& vec) {
	Vector<M> result;
	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < M; ++j) {
			result(i) += mat(i, j) * vec(j);
		}
	}

	return result;
}

template <unsigned N, unsigned M>
inline constexpr const Real& Matrix<N, M>::operator()(unsigned i, unsigned j) const {
#ifdef DEBUG
	if (i >= N || j >= M) throw std::logic_error("Invalid index");
#endif
	
	return _v[i][j];
}

template <unsigned N, unsigned M>
inline constexpr Real& Matrix<N, M>::operator()(unsigned i, unsigned j) {
#ifdef DEBUG
	if (i >= N || j >= M) throw std::logic_error("Invalid index");
#endif

	return _v[i][j];
}

template <unsigned N, unsigned M>
inline constexpr const Real& Matrix<N, M>::operator()(unsigned x) const {
#ifdef DEBUG
	if (x >= N*M) throw std::logic_error("Invalid index");
#endif

	return _v[x%M][x/M];
}

template <unsigned N, unsigned M>
inline constexpr Real& Matrix<N, M>::operator()(unsigned x) {
#ifdef DEBUG
	if (x >= N*M) throw std::logic_error("Invalid index");
#endif

	return _v[x%M][x/M];
}

template <unsigned N, unsigned M>
inline constexpr Matrix<N, M> Matrix<N, M>::operator+(const Matrix<N, M>& mat) const {
	Matrix<N, M> result;
	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < M; ++j) {
			result(i, j) += _v[i][j] + mat(i, j);
		}
	}
	return result;
}	

template <unsigned N, unsigned M>
inline constexpr Matrix<N, M> Matrix<N, M>::operator-(const Matrix<N, M>& mat) const {
	Matrix<N, M> result;
	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < M; ++j) {
			result(i, j) += _v[i][j] - mat(i, j);
		}
	}
	return result;
}

template <unsigned N, unsigned M>
inline constexpr Matrix<N, M> Matrix<N, M>::operator+() const {
	return (*this);
}

template <unsigned N, unsigned M>
inline constexpr Matrix<N, M> Matrix<N, M>::operator-() const {
	return (*this) * (-1);
}

template <unsigned N, unsigned M>
inline constexpr Matrix<N, M> Matrix<N, M>::operator*(const Real& real) const {
	Matrix<N, M> result;
	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < M; ++j) {
			result(i, j) += _v[i][j] * real;
		}
	}
	return result;
}

template <unsigned N, unsigned M>
inline constexpr Matrix<N, M> Matrix<N, M>::operator/(const Real& real) const {
#ifdef DEBUG
	if (real == 0)
		throw std::logic_error("Can't divide by zero");
#endif

	Matrix<N, M> result;
	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < M; ++j) {
			result(i, j) += _v[i][j] / real;
		}
	}
	return result;
}

template <unsigned N, unsigned M>
inline constexpr Matrix<N, M>& Matrix<N, M>::operator*=(const Real& real) {
	return (*this) = (*this) * real;
}

template <unsigned N, unsigned M>
inline constexpr Matrix<N, M>& Matrix<N, M>::operator/=(const Real& real) {
	return (*this) = (*this) / real;
}

template <unsigned N, unsigned M>
template <unsigned K>
inline constexpr Matrix<N, K> Matrix<N, M>::operator*(const Matrix<M, K>& mat) const {
	Matrix<N, K> result;
	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < M; ++j) {
			for (unsigned k = 0; k < K; ++k) {
				result(i, k) += _v[i][j] * mat(j, k);
			}
		}
	}
	return result;
}

template <unsigned N, unsigned M>
inline constexpr Matrix<N, N>& Matrix<N, M>::operator*=(const Matrix<N, N>& mat) {
	static_assert(N == M, "Matrix must be squared for operator*= to work");
	return (*this) = (*this) * mat;
}

template <unsigned N, unsigned M>
inline constexpr Real Matrix<N, M>::det() const {
	throw "not implemented";
	return 0;
}

template <unsigned N, unsigned M>
inline constexpr Matrix<M, N> Matrix<N, M>::transpost() const {
	Matrix<N, M> result;
	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < M; ++j) {
			result(j, i) = _v[i][j];
		}
	}
	return result;
}

template <unsigned N, unsigned M>
inline constexpr Matrix<N, N> Matrix<N, M>::inverse() const {
	static_assert(N == M, "Matrix must be squared for inverse() to work");

	throw "not implemented";
	return {};
}

template <unsigned N, unsigned M>
inline constexpr const Matrix<N, M> Matrix<N, M>::zeros() {
	return Matrix();
}

template <unsigned N, unsigned M>
inline constexpr const Matrix<N, M> Matrix<N, M>::ones() {
	Matrix<N, M> result;
	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < M; ++j) {
			result(j, i) = 1;
		}
	}
	return result;
}

template <unsigned N, unsigned M>
inline constexpr const Matrix<N, M> Matrix<N, M>::eye() {
	Matrix<N, M> result;
	for (unsigned x = 0; x < N*M; ++x)
		result(x) = (x % (M+1) ? 0 : 1);
	return result;
}

}  // math namespace
