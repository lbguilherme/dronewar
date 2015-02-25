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
		Real in = face.normal().x() + face.normal().y() + face.normal().z();
		
		Vector e1 = face.vertices()[1].position() - face.vertices()[0].position();
		Vector e2 = face.vertices()[2].position() - face.vertices()[1].position();
		Vector r1 = face.vertices()[0].position();
		Vector r2 = face.vertices()[1].position();
		
		//result *= (e1 + e2).x() + (e1 + e2).y() + (e1 + e2).z();
		//result *= (r1 + r2).x() + (r1 + r2).y() + (r1 + r2).z();
		result *= e1.x() + e2.x() + e1.y() + e2.y() + e1.z() + e2.z();
		result *= r1.x() + r2.x() + r1.y() + r2.y() + r1.z() + r2.z();
		result /= in;
		result *= (e1.cross(e2)).length();
		
		volume += result;
	}
	
	return volume / 2.0;	
}

Solid Solid::cube(math::Real size) {
	Solid cube;

	// Cube Vertices
	Vertex v1 = cube.addVertex({0, 0, 0});
	Vertex v2 = cube.addVertex({0, 0, size});
	Vertex v3 = cube.addVertex({0, size, size});
	Vertex v4 = cube.addVertex({0, size, 0});
	Vertex v5 = cube.addVertex({size, 0, 0});
	Vertex v6 = cube.addVertex({size, 0, size});
	Vertex v7 = cube.addVertex({size, size, size});
	Vertex v8 = cube.addVertex({size, size, 0});

	// Base
	Edge e12 = cube.addEdge(v1, v2);
	Edge e23 = cube.addEdge(v2, v3);
	Edge e34 = cube.addEdge(v3, v4);
	Edge e14 = cube.addEdge(v1, v4);
	Edge e13 = cube.addEdge(v1, v3);

	// Top
	Edge e56 = cube.addEdge(v5, v6);
	Edge e67 = cube.addEdge(v6, v7);
	Edge e78 = cube.addEdge(v7, v8);
	Edge e58 = cube.addEdge(v5, v8);
	Edge e57 = cube.addEdge(v5, v7);

	// Vertical Sides
	Edge e15 = cube.addEdge(v1, v5);
	Edge e26 = cube.addEdge(v2, v6);
	Edge e37 = cube.addEdge(v3, v7);
	Edge e48 = cube.addEdge(v4, v8);

	// Cross Sides
	Edge e16 = cube.addEdge(v1, v6);
	Edge e27 = cube.addEdge(v2, v7);
	Edge e38 = cube.addEdge(v3, v8);
	Edge e45 = cube.addEdge(v4, v5);

	// Bottom
	cube.addTriangle(e12, e23, e13);
	cube.addTriangle(e13, e34, e14);
	// Top
	cube.addTriangle(e56, e67, e57);
	cube.addTriangle(e57, e78, e58);
	// Right
	cube.addTriangle(e12, e26, e16);
	cube.addTriangle(e56, e15, e16);
	// Left
	cube.addTriangle(e34, e48, e38);
	cube.addTriangle(e78, e37, e38);
	// Front
	cube.addTriangle(e23, e37, e27);
	cube.addTriangle(e67, e26, e27);
	// Back
	cube.addTriangle(e14, e15, e45);
	cube.addTriangle(e58, e48, e45);
	
	return cube;
}
