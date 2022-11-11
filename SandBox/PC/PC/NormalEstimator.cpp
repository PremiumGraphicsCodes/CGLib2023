#include "NormalEstimator.h"

#include "GaussianFunc.h"
#include "Crystal/Space/CompactSpaceHash.h"
#include "CGLib/Math/Matrix3d.h"

using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::PC;


namespace {
	Matrix3df calculateCovarianceMatrix(const Vector3df& center, const std::vector<Vector3df>& neighbors)
	{
		Matrix3df matrix(0, 0, 0, 0, 0, 0, 0, 0, 0);
		for (const auto& p : neighbors) {

			const auto v = center - p;
			//const auto vt = glm::transpose(v);
			//Matrix3df m()
			const auto x00 = v[0] * v[0];
			const auto x01 = v[0] * v[1];
			const auto x02 = v[0] * v[2];
			const auto x10 = v[1] * v[0];
			const auto x11 = v[1] * v[1];
			const auto x12 = v[1] * v[2];
			const auto x20 = v[2] * v[0];
			const auto x21 = v[2] * v[1];
			const auto x22 = v[2] * v[2];

			const Matrix3df m
			(
				x00, x01, x02,
				x10, x11, x12,
				x20, x21, x22
			);

			matrix += m;
		}
		matrix /= neighbors.size();

		return matrix;
	}
}

void NormalEstimator::add(const Vector3df& position)
{
	this->positions.push_back(position);
}

void NormalEstimator::estimate(const float searchRadius)
{
	/*
	this->normals.resize(this->positions.size());
	const auto tableSize = static_cast<int>(this->positions.size());
	CompactSpaceHash spaceHash(searchRadius, tableSize);
	for (const auto& p : positions) {
		spaceHash.add(p);
	}
	const auto g = GaussianFunc::createNormalDistributionFunc();
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
	*/
}
