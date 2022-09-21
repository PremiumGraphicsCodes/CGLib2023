#include "RootScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;

Box3df RootScene::getBoundingBox() const
{
	Box3df bb = Box3df::createDegeneratedBox();
	for (auto c : children) {
		bb.add( c->getBoundingBox() );
	}
	return bb;
}