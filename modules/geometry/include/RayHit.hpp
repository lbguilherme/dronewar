#pragma once

#include <geometry/Ray>
#include <math/Vector>

namespace geometry {

class RayHit {
	friend class Ray;
public:

	math::Real distance() const;
	bool hasHit() const;
	math::Vector3 point() const;

	bool operator<(const RayHit& other) const;

private:

	RayHit(Ray ray);
	RayHit(Ray ray, math::Real distance);

private:

	Ray _ray;
	math::Real _distance;
	bool _hasHit;

};

} // namespace geometry
