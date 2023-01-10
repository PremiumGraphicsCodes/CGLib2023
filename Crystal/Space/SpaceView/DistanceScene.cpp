#include "DistanceScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;

Box3df DistanceScene::getBoundingBox() const
{
	Box3df bb = Box3df::createDegeneratedBox();
	for (const auto& n : nodes) {
		bb.add(n.position);
	}
	return bb;
}
