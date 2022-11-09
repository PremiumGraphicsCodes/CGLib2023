#include "DensityEstimator.h"

#include "Crystal/Space/CompactSpaceHash.h"

using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::PC;

void DensityEstimator::add(const Vector3df& position)
{
	this->positions.push_back(position);
}

void DensityEstimator::estimate(const float searchRadius)
{
	const auto tableSize = static_cast<int>(this->positions.size());
	CompactSpaceHash spaceHash(searchRadius, tableSize);
	for (const auto& p : positions) {
		spaceHash.add(p);
	}
	for (int i = 0; i < tableSize; ++i) {
		const auto indices = spaceHash.findNeighborIndices(i);
	}
}
