#include "VDBPointsScene.h"

#include "../VDB/VDBPoints.h"

using namespace Crystal::Math;
using namespace Crystal::VDB;

Box3df VDBPointsScene::getBoundingBox() const
{
	return shape->getBoundingBox();
}