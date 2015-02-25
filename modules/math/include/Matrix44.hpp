#pragma once

#include <math/Real>
#include <math/Vector4>
#include <stdexcept>

namespace math {

class Matrix44 {
	Real _data[16];
	
public:
	constexpr Matrix44();
	constexpr Matrix44(const Vector4& a, const Vector4& b, const Vector4& c);

	constexpr const Real& operator()(unsigned a, unsigned b) const;
	constexpr Real& operator()(unsigned a, unsigned b);
	
	constexpr const Real& operator()(unsigned a) const;
	constexpr Real& operator()(unsigned a);

	constexpr Matrix44 operator+(const Matrix44& mat) const;
	constexpr Matrix44 operator-(const Matrix44& mat) const;
	
	constexpr Matrix44 operator+() const;
	constexpr Matrix44 operator-() const;
	
	constexpr Matrix44 operator*(const Real& real) const;
	constexpr Matrix44 operator/(const Real& real) const;
	constexpr Matrix44& operator*=(const Real& real);
	constexpr Matrix44& operator/=(const Real& real);
	
	/// Matrix44 multiplication
	constexpr Matrix44 operator*(const Matrix44& mat) const;
	constexpr Matrix44& operator*=(const Matrix44& mat);
	
	// Determinant of the Matrix44
	//constexpr Real det() const;
	
	/// Transpost of the Matrix44
	constexpr Matrix44 transpost() const;
	
	// Inverse of the Matrix44. Assumes Matrix44 is inversible
	//constexpr Matrix44 inverse() const;
	
	/// Returns a null Matrix44.
	constexpr static const Matrix44 zeros();
	
	/// Returns a Matrix44 filled with ones.
	constexpr static const Matrix44 ones();
	
	/// Returns identity Matrix44.
	constexpr static const Matrix44 eye();
};

constexpr Matrix44 operator*(const Real& real, const Matrix44& Matrix44);
constexpr Vector4 operator*(const Matrix44& mat, const Vector4& vec);

constexpr Matrix44 operator*(const Real& real, const Matrix44& Matrix44) {
	return Matrix44 * real;
}

constexpr Vector4 operator*(const Matrix44& mat, const Vector4& vec) {
	Vector4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result(i) += mat(i, j) * vec(j);
		}
	}
	
	return result;
}

inline constexpr Matrix44::Matrix44() : _data{0} {

}

inline constexpr Matrix44::Matrix44(const Vector4& a, const Vector4& b, const Vector4& c) : 
	_data{
		a(0), b(0), c(0),
		a(1), b(1), c(1),
		a(2), b(2), c(2),
		a(3), b(3), c(3),
	} {}

inline constexpr const Real& Matrix44::operator()(unsigned a, unsigned b) const {
	#ifdef DEBUG
	if (a >= 4 || b >= 4) throw std::logic_error("Invalid index");
	#endif
	
	return _data[4*a+b];
}

inline constexpr Real& Matrix44::operator()(unsigned a, unsigned b) {
	#ifdef DEBUG
	if (a >= 4 || b >= 4) throw std::logic_error("Invalid index");
	#endif

	return _data[4*a+b];
}

inline constexpr const Real& Matrix44::operator()(unsigned a) const {
	#ifdef DEBUG
	if (a >= 16) throw std::logic_error("Invalid index");
	#endif

	return _data[a];
}

inline constexpr Real& Matrix44::operator()(unsigned a) {
	#ifdef DEBUG
	if (a >= 16) throw std::logic_error("Invalid index");
	#endif

	return _data[a];
}

inline constexpr Matrix44 Matrix44::operator+(const Matrix44& mat) const {
	Matrix44 result;
	for (int i = 0; i < 16; ++i) result._data[i] = _data[i] + mat(i);
	return result;
}	

inline constexpr Matrix44 Matrix44::operator-(const Matrix44& mat) const {
	Matrix44 result;
	for (int i = 0; i < 16; ++i) result._data[i] = _data[i] - mat(i);
	return result;
}

inline constexpr Matrix44 Matrix44::operator+() const {
	return *this;
}

inline constexpr Matrix44 Matrix44::operator-() const {
	Matrix44 result;
	for (int i = 0; i < 16; ++i) result._data[i] = -_data[i];
	return result;
}

inline constexpr Matrix44 Matrix44::operator*(const Real& real) const {
	Matrix44 result;
	for (int i = 0; i < 16; ++i) result._data[i] = _data[i] * real;
	return result;
}

inline constexpr Matrix44 Matrix44::operator/(const Real& real) const {
	Matrix44 result;
	for (int i = 0; i < 16; ++i) result._data[i] = _data[i] / real;
	return result;
}

inline constexpr Matrix44& Matrix44::operator*=(const Real& real) {
	for (int i = 0; i < 16; ++i) _data[i] *= real;
	return *this;
}

inline constexpr Matrix44& Matrix44::operator/=(const Real& real) {
	#ifdef DEBUG
	if (real == 0) throw std::logic_error("Can't divide by zero");
	#endif

	for (int i = 0; i < 16; ++i) _data[i] /= real;
	return *this;
}

inline constexpr Matrix44 Matrix44::operator*(const Matrix44& mat) const {
	Matrix44 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 4; ++k) {
				result(i, j) += operator()(i, k) * mat(k, j);
			}
		}
	}
	return result;
}

inline constexpr Matrix44& Matrix44::operator*=(const Matrix44& mat) {
	return (*this) = (*this) * mat;
}

/*inline constexpr Real Matrix44::det() const {
	throw "Not implemented";
}*/

inline constexpr Matrix44 Matrix44::transpost() const {
	Matrix44 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result(i, j) = operator()(j, i);
		}
	}
	return result;
}

/*inline constexpr Matrix44 Matrix44::inverse() const {
	throw "Not implemented";
}*/

inline constexpr const Matrix44 Matrix44::zeros() {
	return Matrix44();
}

inline constexpr const Matrix44 Matrix44::ones() {
	Matrix44 result;
	for (int i = 0; i < 16; ++i) result._data[i] = 1;
	return result;
}

inline constexpr const Matrix44 Matrix44::eye() {
	Matrix44 result;
	for (int i = 0; i < 16; ++i) result._data[i] = (i % 5 ? 0 : 1);
	return result;
}

}  // math namespace
