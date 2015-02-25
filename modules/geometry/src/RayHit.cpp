#include <geometry/RayHit>
#include <stdexcept>

using namespace geometry;
using namespace math;

RayHit::RayHit(Ray ray)
	: _ray(ray), _hasHit(false) {

}

RayHit::RayHit(Ray ray, Vector point)
	: _ray(ray), _point(point), _hasHit(true) {

}

bool RayHit::operator<(const RayHit& other) const {
	if (!(this->_ray == other._ray)) throw std::runtime_error("can't compare RayHit from different Rays");
	return distance() < other.distance();
}

Real RayHit::distance() const {
	return (_ray.origin() - _point).length();
}

bool RayHit::hasHit() const {
	return _hasHit;
}

Vector RayHit::point() const {
	return _point;
}
