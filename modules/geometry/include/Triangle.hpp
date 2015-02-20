#include <array>

#include <geometry/Vertex>
#include <geometry/Edge>

namespace geometry {

class Mesh;
class TriangleData;

class Triangle {
	friend class Mesh;

public:

	Triangle(TriangleData* data);
	bool operator<(const Triangle& other) const {return _data < other._data;}
	bool operator==(const Triangle& other) const {return _data == other._data;}

	const std::array<Vertex, 3> vertices() const;
	const std::array<Edge, 3> edges() const;

private:

	TriangleData* _data;

};

}
