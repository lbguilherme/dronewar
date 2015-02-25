#pragma once

#include <geometry/Ray>
#include <math/Vector>

namespace geometry {

class RayHit {
	friend class Ray;
public:

	math::Real distance() const;
	bool hasHit() const;
	math::Vector point() const;

	bool operator<(const RayHit& other) const;

private:

	RayHit(Ray ray);
	RayHit(Ray ray, math::Vector point);

private:

	Ray _ray;
	math::Vector _point;
	bool _hasHit;

};

} // namespace geometry
