#pragma once

#include "CGLib/Math/Vector3d.h"
#include <vector>

namespace Crystal {
	namespace PC {

class DensityEstimator
{
public:
	void add(const Math::Vector3df& position);

	void estimate(const float searchRadius);

	std::vector<float> getDensities() const { return densities; }

private:
	std::vector<Math::Vector3df> positions;
	std::vector<float> densities;
};
	}
}