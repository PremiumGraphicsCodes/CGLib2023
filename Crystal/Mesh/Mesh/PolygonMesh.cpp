#include "PolygonMesh.h"

using namespace Crystal::Math;
using namespace Crystal::Mesh;

PolygonMesh::PolygonMesh() = default;

/*
PolygonMesh::PolygonMesh(const std::vector<Face>&faces, std::vector<std::unique_ptr<Vertex>> && vertices) :
	faces(faces),
	vertices(std::move(vertices))
{
}
*/

Box3df PolygonMesh::getBoundingBox() const
{
	if (vertices.empty()) {
		return Box3df::createDegeneratedBox();
	}
	Math::Box3df bb(vertices.front()->position);
	for (auto& p : vertices) {
		bb.add(p->position);
	}
	return bb;
}
