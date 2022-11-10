#include "PointCloudScene.h"

using namespace Crystal::Math;
using namespace Crystal::PC;

PointCloudScene::PointCloudScene()
{
}

Box3df PointCloudScene::getBoundingBox() const
{
	return shape->getBoindingBox();
}