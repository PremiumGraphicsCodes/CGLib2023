#include "PointCloudScene.h"

using namespace Crystal::Math;
using namespace Crystal::PC;

Box3df PointCloudScene::getBoundingBox() const
{
	return shape->getBoindingBox();
}