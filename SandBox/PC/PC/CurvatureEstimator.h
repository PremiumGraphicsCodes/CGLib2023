#pragma once

#include "CGLib/Math/Vector3d.h"
#include <vector>

namespace Crystal {
	namespace PC {

class CurvatureEstimator
{
public:
	void add(const Math::Vector3df& position);

	void estimate(const float searchRadius);

	std::vector<float> getCurvatures() const { return curvatures; }

private:
	std::vector<Math::Vector3df> positions;
	std::vector<float> curvatures;
};

	}
}