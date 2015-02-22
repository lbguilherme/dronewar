#include <geometry/Solid>
#include <math/Matrix>

using namespace math;
using namespace geometry;


void Solid::orient() {
	for (Triangle face : triangles()) {
		unsigned counter = 0;
		Vector nor = face.normal();
		
		for (Triangle triangle : triangles()) {
			if (face == triangle) continue;
		
			Vector p = face.position() - triangle.vertices()[0].position();
			Vector e1 = triangle.vertices()[1].position() - triangle.vertices()[0].position();
			Vector e2 = triangle.vertices()[2].position() - triangle.vertices()[0].position();
			
			Matrix mat(-nor, e1, e2);
			Vector solution;
			try {
				solution = mat.inverse() * p;
			} catch (std::logic_error&) {
				continue;
			}
			
			if (solution.y() < 0) continue;
			if (solution.z() < 0) continue;
			if (solution.y() > 1) continue;
			if (solution.z() > 1) continue;
			++counter;
		}
		
		if (counter % 2) face.changeOrientation();
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
