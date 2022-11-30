#include "PolygonMesh.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

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
