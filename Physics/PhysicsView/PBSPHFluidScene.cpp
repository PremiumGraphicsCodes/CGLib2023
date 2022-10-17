#include "PBSPHFluidScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

PBSPHFluidScene::PBSPHFluidScene()
{
}

Box3df PBSPHFluidScene::getBoundingBox() const
{
	return fluid->getBoundingBox();
}