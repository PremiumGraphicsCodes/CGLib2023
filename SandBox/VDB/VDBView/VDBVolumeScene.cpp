#include "VDBVolumeScene.h"

#include "../VDB/VDBVolume.h"

using namespace Crystal::Math;
using namespace Crystal::VDB;

Box3df VDBVolumeScene::getBoundingBox() const
{
	return shape->getBoundingBox();
}