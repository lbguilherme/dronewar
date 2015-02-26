#include <geometry/RayHit>
#include <stdexcept>

using namespace geometry;
using namespace math;

RayHit::RayHit(Ray ray)
	: _ray(ray), _hasHit(false) {

}

RayHit::RayHit(Ray ray, math::Real distance)
	: _ray(ray), _distance(distance), _hasHit(true) {

}

bool RayHit::operator<(const RayHit& other) const {
	if (!(this->_ray == other._ray)) throw std::runtime_error("can't compare RayHit from different Rays");
	return distance() < other.distance();
}

Real RayHit::distance() const {
	return _distance;
}

bool RayHit::hasHit() const {
	return _hasHit;
}

Vector3 RayHit::point() const {
	return _ray.origin() + _distance * _ray.direction();
}
