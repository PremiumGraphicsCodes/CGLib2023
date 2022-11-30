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
	auto bb = Box3df::createDegeneratedBox();
	for (const auto& p : positions) {
		bb.add(p);
	}
	return bb;
}