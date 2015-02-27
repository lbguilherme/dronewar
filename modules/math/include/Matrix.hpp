#pragma once

#include <math/Real>
#include <math/Vector>
#include <stdexcept>
#include <array>
#include <utility>
#include <type_traits>

namespace math {

enum class ReductionType;
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
	constexpr Matrix<N, M> transpost() const;
	
	/// Creates a reduced matrix of echelon form, from line-equivalent operations
	
	template <typename ReductionHelper>
	constexpr Matrix<M, N> rref(ReductionHelper&& reductionHelper, ReductionType type) const;
	constexpr Matrix<M, N> rref(ReductionType type) const;
	constexpr Matrix<M, N> rref(Real& real, ReductionType type) const;
	constexpr Matrix<M, N> rref(Vector<M>& vec, ReductionType type) const;
	constexpr Matrix<M, N> rref(Matrix<M, N>& mat, ReductionType type) const;
	
	/*
	template <typename... Args>
	constexpr Matrix<M, N> rref(ReductionType type, Args&... args) const;
	*/
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
	
	void swapline(unsigned a, unsigned b);
	
	

private:

	std::array<std::array<Real, N>, M> _v;

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
	Real reals[] = {Real(head), Real(tail)...};

	for (unsigned i = 0; i < M; ++i)
		for (unsigned j = 0; j < N; ++j)
			_v[i][j] = reals[i*N+j];
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
	if (i >= M || j >= N) throw std::logic_error("Invalid index");
#endif
	
	return _v[i][j];
}

template <unsigned M, unsigned N>
inline constexpr Real& Matrix<M, N>::operator()(unsigned i, unsigned j) {
#ifdef DEBUG
	if (i >= M || j >= N) throw std::logic_error("Invalid index");
#endif

	return _v[i][j];
}

template <unsigned M, unsigned N>
inline constexpr const Real& Matrix<M, N>::operator()(unsigned x) const {
#ifdef DEBUG
	if (x >= N*M) throw std::logic_error("Invalid index");
#endif

	return _v[x%N][x/N];
}

template <unsigned M, unsigned N>
inline constexpr Real& Matrix<M, N>::operator()(unsigned x) {
#ifdef DEBUG
	if (x >= N*M) throw std::logic_error("Invalid index");
#endif

	return _v[x%N][x/N];
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
inline constexpr Matrix<N, M> Matrix<M, N>::transpost() const {
	Matrix<N, M> result;
	for (unsigned i = 0; i < M; ++i) {
		for (unsigned j = 0; j < N; ++j) {
			result(j, i) = _v[i][j];
		}
	}
	return result;
}

namespace internal {
	template <unsigned M, unsigned N>
	struct ReductionHelperWithMatrix {
		Matrix<M, N>& mat;
		
		void applyLineSwap(unsigned a, unsigned b) {mat.swapline(a, b);}
		void applySubtractLines(unsigned a, unsigned b) {
			for (unsigned j = 0; j < N; ++j) mat(a, j) -= mat(b, j);
		}
		
		void applyScalar(unsigned a, Real s) {
			for (unsigned j = 0; j < N; ++j) mat(a, j) *= s;
		}
	};
	
	template <unsigned M>
	struct ReductionHelperWithVector {
		Vector<M>& vec;
		void applyLineSwap(unsigned a, unsigned b) {vec.swapline(a, b);}
		void applySubtractLines(unsigned a, unsigned b) {vec(a) -= vec(b);}
		void applyScalar(unsigned a, Real s) {vec(a) *= s;}
	};
	
	struct ReductionHelperWithReal {
		Real& real;
		
		void applyLineSwap(unsigned, unsigned) { real *= (-1);}
		void applySubtractLines(unsigned, unsigned) {}
		void applyScalar(unsigned, Real s) {real *= s;}
	};
	
	struct ReductionHelperWithNothing {
		void applyLineSwap(unsigned, unsigned) {}
		void applySubtractLines(unsigned, unsigned) {}
		void applyScalar(unsigned, Real) {}
	};
	
	template <typename... T>
	struct ReductionHelperMerger;
	
	template <typename Helper, typename... Others>
	struct ReductionHelperMerger<Helper, Others...> {
		Helper& h1;
		ReductionHelperMerger<Others...>& h2;
		void applyLineSwap(unsigned a, unsigned b) {h1.applyLineSwap(a, b); h2.applyLineSwap(a, b);}
		void applySubtractLines(unsigned a, unsigned b) {h1.applySubtractLines(a, b); h2.applySubtractLines(a, b);}
		void applyScalar(unsigned a, Real s) {h1.applyScalar(a, s); h2.applyScalar(a, s);}
	};
	
	template <>
	struct ReductionHelperMerger<> {
		void applyLineSwap(unsigned, unsigned) {}
		void applySubtractLines(unsigned, unsigned) {}
		void applyScalar(unsigned, Real) {}
	};
	
	template <typename... T>
	struct ReductionHelperGetter;
	
	template <typename Head, typename... T>
	struct ReductionHelperGetter<Head, T...> {
		static auto get(Head& head, T&... x) {
			return ReductionHelperMerger<decltype(ReductionHelperGetter<Head>::get(head)), decltype(ReductionHelperGetter<T>::get(x))...>
				{ReductionHelperGetter<Head>::get(head), ReductionHelperGetter<Head>::get(x)...};
		}
	};
	
	template <>
	struct ReductionHelperGetter<> {
		static ReductionHelperWithNothing get() { return {}; }
	};
	
	template <>
	struct ReductionHelperGetter<Real> {
		static ReductionHelperWithReal get(Real& x) { return {x}; }
	};
	
	template <unsigned M>
	struct ReductionHelperGetter<Vector<M>> {
		static ReductionHelperWithVector<M> get(Vector<M>& x) { return {x}; }
	};
	
	template <unsigned M, unsigned N>
	struct ReductionHelperGetter<Matrix<M, N>> {
		static ReductionHelperWithMatrix<M, N> get(Matrix<M, N>& x) { return {x}; }
	};
	
	
	
} // internal

enum class ReductionType {
	UpperLeft, UpperRight,
	LowerLeft, LowerRight
};


template <unsigned M, unsigned N>
inline constexpr Matrix<M, N> Matrix<M, N>::rref(ReductionType type) const {
	return rref(internal::ReductionHelperWithNothing{}, type);
}

template <unsigned M, unsigned N>
inline constexpr Matrix<M, N> Matrix<M, N>::rref(Real& real, ReductionType type) const {
	return rref(internal::ReductionHelperWithReal{real}, type);
}

template <unsigned M, unsigned N>
inline constexpr Matrix<M, N> Matrix<M, N>::rref(Vector<M>& vec, ReductionType type) const {
	return rref(internal::ReductionHelperWithVector<M>{vec}, type);
}

template <unsigned M, unsigned N>
inline constexpr Matrix<M, N> Matrix<M, N>::rref(Matrix<M, N>& mat, ReductionType type) const {
	return rref(internal::ReductionHelperWithMatrix<M, N>{mat}, type);
}

/*
template <unsigned M, unsigned N>
template <typename... Args>
inline constexpr Matrix<M, N> Matrix<M, N>::rref(ReductionType type, Args&... args) const {
	Matrix<M, N> result = *this;
	//auto helper = internal::ReductionHelperGetter<Matrix<M, N>, Args...>::get(result, args...);*/


template <unsigned M, unsigned N>
template <typename ReductionHelper>
inline constexpr Matrix<M, N> Matrix<M, N>::rref(ReductionHelper&& reductionHelper, ReductionType type) const {
	
	Matrix<M, N> result = *this;
	internal::ReductionHelperWithMatrix<M, N> helper{result};
	
	// Iterate until run out of (rows or cols).
	for (unsigned k = 0; k < M-1 or k < N-1; ++k) {
		
		// Pivot indicator
		bool null = false;
		
		// Check if main pivot is zero. If it is, fix it!
		Real pivot = 0;
		unsigned ip = 0;
		unsigned jp = 0;
		switch (type) {
			case ReductionType::LowerRight: ip = k; jp = N-k-1; break;
			case ReductionType::LowerLeft:  ip = k; jp = k; break;
			case ReductionType::UpperRight: ip = N-k-1; jp = N-k-1; break;
			case ReductionType::UpperLeft:  ip = N-k-1; jp = k; break;
		}
		pivot = result(ip, jp);
		
		if (pivot == 0) {
			null = true;
			for (unsigned i = k+1; i < M; ++i) {
				Real cell = 0;
				unsigned ic = 0;
				unsigned jc = 0;
				switch (type) {
					case ReductionType::LowerRight: ic = i; jc = N-k-1; break;
					case ReductionType::LowerLeft:  ic = i; jc = k; break;
					case ReductionType::UpperRight: ic = N-i-1; jc = N-k-1; break;
					case ReductionType::UpperLeft:  ic = N-i-1; jc = k; break;
				}
				cell = result(ic, jc);
				
				if (cell != 0) {
					reductionHelper.applyLineSwap(ip, ic);
					helper.applyLineSwap(ip, ic);
					null = false;
					break;
				}
			}
		}
		
		// No pivot found. Go on...
		if (null) continue;
	
		for (unsigned i = k+1; i < M; ++i) {
			Real cell = 0;
			unsigned ic = 0;
			unsigned jc = 0;
			switch (type) {
				case ReductionType::LowerRight: ic = i; jc = N-k-1; break;
				case ReductionType::LowerLeft:  ic = i; jc = k; break;
				case ReductionType::UpperRight: ic = N-i-1; jc = N-k-1; break;
				case ReductionType::UpperLeft:  ic = N-i-1; jc = k; break;
			}
			cell = result(ic, jc);

			// Already reduced. Move on.
			if (cell == 0) continue;
			
			// Reduce the matrix
			Real value = pivot / cell;
			
			reductionHelper.applyScalar(ic, value);
			reductionHelper.applySubtractLines(ic, ip);
			
			helper.applyScalar(ic, value);
			helper.applySubtractLines(ic, ip);
		}
	}
	
	return result;
}

template <unsigned M, unsigned N>
inline constexpr Real Matrix<M, N>::det() const {
	static_assert(M == N, "Matrix must be squared for det() to work");

	Real result = 1;
	Matrix<M, M> reduced = rref(result, ReductionType::LowerLeft);
	for (unsigned i = 0; i < M; ++i) result *= reduced(i, i);
	return result;
}

template <unsigned M, unsigned N>
inline constexpr Matrix<N, N> Matrix<M, N>::inverse() const {
	static_assert(M == N, "Matrix must be squared for inverse() to work");
	
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
			result(i, j) = 1;
		}
	}
	return result;
}

template <unsigned M, unsigned N>
inline constexpr const Matrix<M, N> Matrix<M, N>::eye() {
	Matrix<M, N> result;
	for (unsigned x = 0; x < M*N; ++x)
		result(x) = (x % (N+1) ? 0 : 1);
	return result;
}

template <unsigned M, unsigned N>
void Matrix<M, N>::swapline(unsigned a, unsigned b) {
	for (unsigned j = 0; j < N; ++j) 
		std::swap(_v[a][j], _v[b][j]);
}

}  // math namespace
