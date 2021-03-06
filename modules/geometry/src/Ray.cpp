#include <geometry/Ray>
#include <math/Matrix>

using namespace geometry;
using namespace math;

Ray::Ray(Vector3 origin, Vector3 direction)
	: _origin(origin), _direction(direction) {

}

Vector3 Ray::origin() const {
	return _origin;
}

Vector3 Ray::direction() const {
	return _direction;
}

bool Ray::operator==(const Ray& other) const {
	return _origin == other._origin && _direction == other._direction;
}

RayHit Ray::castOnTriangle(Triangle triangle) const {
	Vector3 p = _origin - triangle.vertices()[0].position();
	Vector3 ej = triangle.vertices()[1].position() - triangle.vertices()[0].position();
	Vector3 ek = triangle.vertices()[2].position() - triangle.vertices()[0].position();

	Vector3 solution;
	Matrix3 mat(-_direction, ej, ek);

	try {
		solution = mat.inverse() * p;
	} catch (std::logic_error&) {
		return RayHit{*this};
	}

	if (solution.x() < 0) return RayHit{*this};
	if (solution.y() < 0) return RayHit{*this};
	if (solution.z() < 0) return RayHit{*this};
	if (solution.y() > 1) return RayHit{*this};
	if (solution.z() > 1) return RayHit{*this};

	Real w = -solution.y()-solution.z()+1;

	if (w < 0) return RayHit{*this};
	if (w > 1) return RayHit{*this};

	return RayHit{*this, solution.x()};
}

RayHitSet Ray::castOnMesh(const Mesh& mesh) const {
	RayHitSet hits;
	for (Triangle t : mesh.triangles()) {
		RayHit hit = castOnTriangle(t);
		if (hit.hasHit())
			hits.insert(hit);
	}

	hits.removeDuplicates();

	return hits;
}
