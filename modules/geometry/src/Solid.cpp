#include <geometry/Solid>
#include <geometry/Ray>
#include <geometry/RayHit>
#include <math/Matrix>

using namespace math;
using namespace geometry;


void Solid::orient() {
	for (Triangle face : triangles()) {
		Ray ray{face.position(), face.normal()};
		if (ray.castOnMesh(*this).size() % 2 == 0)
			face.changeOrientation();
	}
}

Real Solid::volume() const {
	Real volume = 0;
	for (Triangle face : triangles()) {
		Real result = 1;
		Real in = face.normal().x();
		
		Vector e1 = face.vertices()[1].position() - face.vertices()[0].position();
		Vector e2 = face.vertices()[2].position() - face.vertices()[1].position();
		Vector r1 = face.vertices()[0].position();
		Vector r2 = face.vertices()[1].position();
		
		result *= (e1 + e2).x();
		result *= (r1 + r2).x();
		result /= in * in;
		result *= (e1.cross(e2)).length();
		
		volume += result;
	}
	
	return volume;	
}
