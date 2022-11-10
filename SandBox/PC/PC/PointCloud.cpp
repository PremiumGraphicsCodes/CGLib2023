#include "PointCloud.h"

using namespace Crystal::Math;
using namespace Crystal::PC;

void PointCloud::add(std::unique_ptr<IPoint>&& point)
{
	points.push_back(std::move(point));
}

Box3df PointCloud::getBoindingBox() const
{
	auto bb = Math::Box3df::createDegeneratedBox();
	for (auto& p : points) {
		bb.add(p->getPosition());
	}
	return bb;
}
