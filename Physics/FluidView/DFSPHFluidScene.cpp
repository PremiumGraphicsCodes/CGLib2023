#include "DFSPHFluidScene.h"

#include <cassert>

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

DFSPHFluidScene::DFSPHFluidScene()
{
	//assert(false);
}

Box3df DFSPHFluidScene::getBoundingBox() const
{
	return fluid->getBoundingBox();
}