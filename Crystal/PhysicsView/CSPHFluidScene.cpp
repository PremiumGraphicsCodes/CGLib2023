#include "CSPHFluidScene.h"

#include <cassert>

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

CSPHFluidScene::CSPHFluidScene()
{
	//assert(false);
}

Box3df CSPHFluidScene::getBoundingBox() const
{
	return Box3df();
	//return shape->getBoundingBox();
}