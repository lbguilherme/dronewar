#pragma once

#include <geometry/Mesh>
#include <math/Real>

namespace geometry {

class RayHit;
class RayHitSet;

class Ray {
public:

	Ray(math::Vector origin, math::Vector direction);

	RayHit castOnTriangle(Triangle triangle) const;
	RayHitSet castOnMesh(const Mesh& mesh) const;

	math::Vector origin() const;
	math::Vector direction() const;

	bool operator==(const Ray& other) const;

private:

	math::Vector _origin;
	math::Vector _direction;

};

} // namespace geometry

#include <geometry/RayHit>
#include <geometry/RayHitSet>
