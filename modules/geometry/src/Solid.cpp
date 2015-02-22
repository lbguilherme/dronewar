#include <geometry/Solid>
#include <math/Matrix>

using namespace math;
using namespace geometry;


void Solid::orient() {
	for (Triangle face : triangles()) {
	
		unsigned counter = 0;
		for (Triangle triangle : triangles()) {
			if (face == triangle) continue;
		
			Vector p = face.vector() - triangle.vertices()[0].vector();
			Vector e1 = triangle.vertices()[1].vector() - triangle.vertices()[0].vector();
			Vector e2 = triangle.vertices()[2].vector() - triangle.vertices()[0].vector();
			
			Matrix mat(-triangle.normal(), e1, e2);
			Vector solution = mat.inverse() * p;
			
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
	throw "not implemented";
}
