#include "MVPFluidScene.h"

#include <cassert>

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

MVPFluidScene::MVPFluidScene()
{
	//assert(false);
}

Box3df MVPFluidScene::getBoundingBox() const
{
	return fluid->getBoundingBox();
}