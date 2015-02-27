#pragma once

#include <set>

#include <math/Vector>
#include <geometry/Vertex>
#include <geometry/Edge>
#include <geometry/Triangle>
#include <geometry/Transform>

namespace geometry {

/*!
 * \brief The Mesh class represents a collection of vertices, edges and triangles.
 *
 * Vertices can be freely placed on space as long as no two vertices are identical.
 * They are shared between edges and triangles. Similary, edges are shared between triangles.
 *
 * The focus of a Mesh is the triangles. There can exist vertices or edges without a connected triangle,
 * but they won't be stored nor handled by some functions. For most scenarios, Mesh will act as if they
 * don't exist, so don't rely on it.
 *
 * - Every vertex can connect any number of edges and triangles.
 * - A edge connects exactly two points and any number of triangles.
 * - The triangles have exactly three vertices and three edges.
 *
 * Notice that a Mesh is not required to be closed, manifold, nor connected. It can be seen simply as a set of triangles.
 *
 * A mesh entity is either a Vertex, an Edge or a Triangle.
 */
class Mesh {
public:

	/// Constructs a empty Mesh. It contains no mesh entities.
	Mesh();

	/// It is not allowed to copy a Mesh. This operation would be too slow and is not really required. You should use moves.
	Mesh(const Mesh&) = delete;

	/// Moves a Mesh. The Mesh from where you moved will be empty as if it were default-constructed.
	Mesh(Mesh&& other);

	/// \brief Deletes a Mesh and all associated entities.
	///
	/// Note that after a Mesh is destroyed
	/// any use of a entity that used to be on this Mesh is now invalid
	~Mesh();

	/// Returns a collection of all vertices contained by this Mesh. This collection follows no specific order.
	const std::set<Vertex>& vertices() const;

	/// Returns a collection of all edges contained by this Mesh. This collection follows no specific order.
	const std::set<Edge>& edges() const;

	/// Returns a collection of all triangles contained by this Mesh. This collection follows no specific order.
	const std::set<Triangle>& triangles() const;

	/// \brief Insert a new vertex on the mesh.
	///
	/// Be careful to never insert two vertices on the same position as it will
	/// break the assumption that all entities are uniq. This function is currently unable to check if the given
	/// point is already occupied by another vertex. The returned Vertex object is internally linked to this
	/// Mesh and a change to it may affect other entities. Refer to the Vertex documentation for details.
	/// \note This function is exception-safe. If any exception happens, Mesh will remain unchanged.
	Vertex addVertex(math::Vector3 point);

	/// \brief Insert a new edge on the mesh.
	///
	/// This functions checks if the edge requested already exist, if so, it returns the Edge.
	/// This means you can call this funcion multiple times or use it to retrive an existing edge given two vertices.
	/// The returned Edge object is internally linked to this Mesh and a change to it may affect other entities.
	/// Refer to the Edge documentation for details.
	/// \note This function is exception-safe. If any exception happens, Mesh will remain unchanged.
	Edge addEdge(Vertex v1, Vertex v2);

	/// \brief Insert a new triangle on the mesh.
	///
	/// This functions checks if the triangle requested already exist, if so, it returns the Triangle.
	/// This means you can call this funcion multiple times or use it to retrive an existing triangle given three vertices.
	/// The returned Triangle object is internally linked to this Mesh and a change to it may affect other entities.
	/// Refer to the Triangle documentation for details.
	/// \note This function is exception-safe. If any exception happens, Mesh will remain unchanged.
	Triangle addTriangle(Vertex v1, Vertex v2, Vertex v3);

	/// \brief Insert a new triangle on the mesh.
	///
	/// This functions checks if the triangle requested already exist, if so, it returns the Triangle.
	/// This means you can call this funcion multiple times or use it to retrive an existing triangle given three edges.
	/// The returned Triangle object is internally linked to this Mesh and a change to it may affect other entities.
	/// Refer to the Triangle documentation for details.
	/// \note This function is exception-safe. If any exception happens, Mesh will remain unchanged.
	Triangle addTriangle(Edge e1, Edge e2, Edge e3);
	
	/// Applies a transformation in the mesh
	void apply(const Transform& transform);

	/// \brief Write all mesh data into a stream.
	///
	/// The file format is very similar to Wavefront OBJ, but is not compactible in any way. The format is text based and can
	/// be easily transfered between other applications. Note that only triangles are stored, any vertex or edge not connected
	/// to a triangle will be dropped.
	void write(std::ostream& out) const;

	/// \brief Reads and creates a new mesh from a stream.
	///
	/// It expects the same format used by write().
	static Mesh read(std::istream &in);

private:

	std::set<Vertex> _vertices;      //!< The internal list of vertices. This is required for iteration and destruction.
	std::set<Edge> _edges;           //!< The internal list of edges. This is required for iteration and destruction.
	std::set<Triangle> _triangles;   //!< The internal list of triangles. This is required for iteration and destruction.
	
};

}

