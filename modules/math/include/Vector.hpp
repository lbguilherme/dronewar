#pragma once

#include <math/Real>
#include <cmath>
#include <stdexcept>
#include <array>
#include <algorithm>

namespace math {

template <unsigned D>
class Vector {
	static_assert(D > 0, "Can't make a vector with no dimentions");
public:

	constexpr Vector();

	constexpr Vector(const Vector<D>& other);
	constexpr Vector(Vector<D>& other);

	template <typename... Args>
	constexpr Vector(const Args&... args);

	template <unsigned E, typename... Args>
	constexpr Vector(const Vector<E>& vec, Args&&... args);

	constexpr bool isNan() const;

	constexpr Real x() const;
	constexpr Real y() const;
	constexpr Real z() const;
	constexpr Real t() const;
	constexpr const Real& operator()(unsigned i) const;
	constexpr Real& operator()(unsigned i);

	constexpr Vector operator+(const Vector<D>& vec) const;
	constexpr Vector operator-(const Vector<D>& vec) const;
	
	constexpr Vector operator+() const;
	constexpr Vector operator-() const;
	
	constexpr Vector operator*(const Real& real) const;
	constexpr Vector operator/(const Real& real) const;
	
	/// Component-wise multiplication between vectors
	constexpr Vector operator*(const Vector<D>& vec) const;
	
	/// Component-wise division between vectors
	constexpr Vector operator/(const Vector<D>& vec) const;
	
	/// Component-wise multiplication between vectors
	constexpr Vector<D>& operator*=(const Vector<D>& vec);
	
	/// Component-wise division between vectors
	constexpr Vector<D>& operator/=(const Vector<D>& vec);
	
	constexpr Vector<D>& operator+=(const Vector<D>& vec);
	constexpr Vector<D>& operator-=(const Vector<D>& vec);
	constexpr Vector<D>& operator*=(const Real& real);
	constexpr Vector<D>& operator/=(const Real& real);
	
	constexpr bool operator>(const Vector<D>& vec) const;
	constexpr bool operator<(const Vector<D>& vec) const;
	constexpr bool operator>=(const Vector<D>& vec) const;
	constexpr bool operator<=(const Vector<D>& vec) const;
	constexpr bool operator==(const Vector<D>& vec) const;
	
	/// The dot product of a vector with another vector
	constexpr Real dot(const Vector<D>& vec) const;
	
	/// Returns the dot product of a vector with itself
	constexpr Real dotself() const;
	
	/// Returns the length of a vector
	Real length() const; // requires sqrt which is not constexpr. How fix?
	
	/// Returns the cross product of a vector
	constexpr Vector cross(const Vector<D>& vec) const;
	
	/// Returns the unit vector
	constexpr Vector unit() const;

	template <unsigned E>
	constexpr Vector<E> subvector() const;
	
	void swapline(unsigned a, unsigned b);

private:

	std::array<Real, D> _v;

};

using Vector2 = Vector<2>;
using Vector3 = Vector<3>;
using Vector4 = Vector<4>;

template <unsigned D>
inline constexpr Vector<D>::Vector() {
	for (unsigned i = 0; i < D; ++i)
		_v[i] = 0;
}

template <unsigned D>
inline constexpr Vector<D>::Vector(const Vector<D>& other) : _v(other._v) {

}

template <unsigned D>
inline constexpr Vector<D>::Vector(Vector<D>& other) : _v(other._v) {

}

template <unsigned D>
template <typename... Args>
inline constexpr Vector<D>::Vector(const Args&... args) : _v{{Real(args)...}}
{
	static_assert(sizeof...(Args) == D, "Invalid number of constructor arguments");
}

template <unsigned D>
template <unsigned E, typename... Args>
inline constexpr Vector<D>::Vector(const Vector<E>& vec, Args&&... args) : _v{}
{
	static_assert(sizeof...(Args) == D-E, "Invalid number of constructor arguments");
	Real pack[] = {Real(args)...};

	for (unsigned i = 0; i < E; ++i)
		_v[i] = vec(i);

	for (unsigned i = E; i < D; ++i)
		_v[i] = pack[E-i];
}

template <unsigned D>
constexpr Vector<D> operator*(const Real& real, const Vector<D>& vec) {
	return vec * real;
}

template <unsigned D>
inline constexpr bool Vector<D>::isNan() const {
	for (unsigned i = 0; i < D; ++i)
		if (_v[i] != _v[i])
			return true;
	return false;
}

template <unsigned D>
inline constexpr Real Vector<D>::dot(const Vector<D>& vec) const {
	Real result = 0;
	for (unsigned i = 0; i < D; ++i)
		result += _v[i] * vec._v[i];
	return result;
}

template <unsigned D>
inline constexpr Real Vector<D>::dotself() const {
	return dot(*this);
}

template <unsigned D>
inline Real Vector<D>::length() const {
	return std::sqrt(dot(*this));
}

template <unsigned D>
inline constexpr Vector<D> Vector<D>::cross(const Vector<D>& vec) const {
	static_assert(D == 3, "Invalid number of dimentions for cross product");
	return {
		_v[1]*vec._v[2] - _v[2] * vec._v[1],
		_v[2]*vec._v[0] - _v[0] * vec._v[2],
		_v[0]*vec._v[1] - _v[1] * vec._v[0]
	};
}

template <unsigned D>
inline constexpr Vector<D> Vector<D>::unit() const {
	return (*this) / length();
}

template <unsigned D>
inline constexpr Real Vector<D>::x() const {
	static_assert(D >= 1, "Invalid number of dimentions for x component");
	return _v[0];
}

template <unsigned D>
inline constexpr Real Vector<D>::y() const {
	static_assert(D >= 2, "Invalid number of dimentions for y component");
	return _v[1];
}

template <unsigned D>
inline constexpr Real Vector<D>::z() const {
	static_assert(D >= 3, "Invalid number of dimentions for z component");
	return _v[2];
}

template <unsigned D>
inline constexpr Real Vector<D>::t() const {
	static_assert(D >= 4, "Invalid number of dimentions for t component");
	return _v[3];
}

template <unsigned D>
inline constexpr const Real& Vector<D>::operator()(unsigned i) const {
#ifdef DEBUG
	if (i >= D)
		throw std::logic_error("Invalid index");
#endif

	return _v[i];
}

template <unsigned D>
inline constexpr Real& Vector<D>::operator()(unsigned i) {
#ifdef DEBUG
	if (i >= D)
		throw std::logic_error("Invalid index");
#endif

	return _v[i];
}

template <unsigned D>
inline constexpr Vector<D> Vector<D>::operator+(const Vector<D>& vec) const {
	Vector<D> result;
	for (unsigned i = 0; i < D; ++i)
		result._v[i] = _v[i] + vec._v[i];
	return result;
}

template <unsigned D>
inline constexpr Vector<D> Vector<D>::operator-(const Vector<D>& vec) const {
	Vector<D> result;
	for (unsigned i = 0; i < D; ++i)
		result._v[i] = _v[i] - vec._v[i];
	return result;
}

template <unsigned D>
inline constexpr Vector<D> Vector<D>::operator+() const {
	return (*this);
}

template <unsigned D>
inline constexpr Vector<D> Vector<D>::operator-() const {
	return (*this) * (-1);
}

template <unsigned D>
inline constexpr Vector<D> Vector<D>::operator*(const Vector<D>& vec) const {
	Vector<D> result;
	for (unsigned i = 0; i < D; ++i)
		result._v[i] = _v[i] * vec._v[i];
	return result;
}

template <unsigned D>
inline constexpr Vector<D> Vector<D>::operator*(const Real& real) const {
	Vector<D> result;
	for (unsigned i = 0; i < D; ++i)
		result._v[i] = _v[i] * real;
	return result;
}

template <unsigned D>
inline constexpr Vector<D> Vector<D>::operator/(const Vector<D>& vec) const {
#ifdef DEBUG
	for (unsigned i = 0; i < D; ++i)
		if (vec._v[i] == 0)
			throw std::logic_error("Can't divide by zero");
#endif

	Vector<D> result;
	for (unsigned i = 0; i < D; ++i)
		result._v[i] = _v[i] / vec._v[i];
	return result;
}

template <unsigned D>
inline constexpr Vector<D> Vector<D>::operator/(const Real& real) const {
#ifdef DEBUG
	if (real == 0)
		throw std::logic_error("Can't divide by zero");
#endif

	Vector<D> result;
	for (unsigned i = 0; i < D; ++i)
		result._v[i] = _v[i] / real;
	return result;
}

template <unsigned D>
inline constexpr Vector<D>& Vector<D>::operator+=(const Vector<D>& vec) {
	return (*this) = (*this) + vec;
}

template <unsigned D>
inline constexpr Vector<D>& Vector<D>::operator-=(const Vector<D>& vec) {
	return (*this) = (*this) - vec;
}

template <unsigned D>
inline constexpr Vector<D>& Vector<D>::operator*=(const Vector<D>& vec) {
	return (*this) = (*this) * vec;
}

template <unsigned D>
inline constexpr Vector<D>& Vector<D>::operator/=(const Vector<D>& vec) {
	return (*this) = (*this) / vec;
}

template <unsigned D>
inline constexpr Vector<D>& Vector<D>::operator*=(const Real& real) {
	return (*this) = (*this) / real;
}

template <unsigned D>
inline constexpr Vector<D>& Vector<D>::operator/=(const Real& real) {
	return (*this) = (*this) / real;
}

template <unsigned D>
inline constexpr bool Vector<D>::operator>(const Vector<D>& vec) const {
	return dotself() > vec.dotself();
}

template <unsigned D>
inline constexpr bool Vector<D>::operator<(const Vector<D>& vec) const {
	return dotself() < vec.dotself();
}

template <unsigned D>
inline constexpr bool Vector<D>::operator>=(const Vector<D>& vec) const {
	return dotself() >= vec.dotself();
}

template <unsigned D>
inline constexpr bool Vector<D>::operator<=(const Vector<D>& vec) const {
	return dotself() <= vec.dotself();
}

template <unsigned D>
inline constexpr bool Vector<D>::operator==(const Vector<D>& vec) const {
	for (unsigned i = 0; i < D; ++i)
		if (_v[i] != vec._v[i])
			return false;
	return true;
}

template <unsigned D>
template <unsigned E>
inline constexpr Vector<E> Vector<D>::subvector() const {
	static_assert(E <= D, "Invalid number of dimentions for subvector");
	Vector<E> result;
	for (unsigned i = 0; i < E; ++i)
		result(i) = _v[i];
	return result;
}

template <unsigned D>
void Vector<D>::swapline(unsigned a, unsigned b) {
	std::swap(_v[a], _v[b]);
}

} // math namespace
