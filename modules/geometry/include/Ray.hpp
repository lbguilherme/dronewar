#pragma once

#include <geometry/Mesh>
#include <math/Real>

namespace geometry {

class RayHit;
class RayHitSet;

class Ray {
public:

	Ray(math::Vector3 origin, math::Vector3 direction);

	RayHit castOnTriangle(Triangle triangle) const;
	RayHitSet castOnMesh(const Mesh& mesh) const;

	math::Vector3 origin() const;
	math::Vector3 direction() const;

	bool operator==(const Ray& other) const;

private:

	math::Vector3 _origin;
	math::Vector3 _direction;

};

} // namespace geometry

#include <geometry/RayHit>
#include <geometry/RayHitSet>
