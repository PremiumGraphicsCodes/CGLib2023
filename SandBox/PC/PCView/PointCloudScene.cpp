#include "PointCloudScene.h"

using namespace Crystal::Math;
using namespace Crystal::PC;

Box3df PointCloud::getBoundingBox() const
{
	auto bb = Box3df::createDegeneratedBox();
	for (const auto& p : points) {
		bb.add(p->getPosition());
	}
	return bb;
}

PointCloudScene::PointCloudScene()
{
}

Box3df PointCloudScene::getBoundingBox() const
{
	return shape->getBoundingBox();
}