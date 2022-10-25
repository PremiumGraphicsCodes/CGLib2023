#pragma once

#include "CGLib/Math/Vector3d.h"
#include "CGLib/Math/Matrix3d.h"

#include <vector>

namespace Crystal {
	namespace Physics {

class WPCA
{
public:
	Math::Matrix3df calculateCovarianceMatrix(const Math::Vector3df& center, const std::vector<Math::Vector3df>& positions, const float radius);

	Math::Vector3df calculateWeightedMean(const Math::Vector3df& center, const std::vector<Math::Vector3df>& positions, const float radius);

	float calculateWeight(const Math::Vector3df& lhs, const Math::Vector3df& rhs, const float radius);

	void setup(const Math::Vector3df& center, const std::vector<Math::Vector3df>& positions, const float radius);

private:
	class PositionWeight
	{
	public:
		Math::Vector3df position;
		float weight;
	};

	std::vector<PositionWeight> pws;
	float totalWeight;
};

	}
}