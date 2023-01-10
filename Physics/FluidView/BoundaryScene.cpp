#include "BoundaryScene.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

Box3df BoundaryScene::getBoundingBox() const
{
	Box3df bb = Box3df::createDegeneratedBox();
	for (const auto& n : nodes) {
		bb.add(n.position);
	}
	return bb;
}
