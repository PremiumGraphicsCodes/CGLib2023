#include "DensityEstimator.h"

#include "CGLib/Math/Gaussian.h"
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
	this->densities.resize(this->positions.size());
	const auto tableSize = static_cast<int>(this->positions.size());
	CompactSpaceHash spaceHash(searchRadius, tableSize);
	for (const auto& p : positions) {
		spaceHash.add(p);
	}
	const auto g = Gaussian::createNormalDistributionFunc();
	for (int i = 0; i < tableSize; ++i) {
		const auto& p = this->positions[i];
		const auto indices = spaceHash.findNeighborIndices(i);
		float density = 0.0f;
		for (const auto ni : indices) {
			const auto n = this->positions[ni];
			const auto d = Math::getDistance(p, n);
			const auto w = g.getWeight(d / searchRadius);
			density += w;
		}
		this->densities[i] = density;
	}
}
 