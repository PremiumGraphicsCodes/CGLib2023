#pragma once

#include "CGLib/Math/Vector3d.h"
#include <vector>

namespace Crystal {
	namespace PC {

class NormalEstimator
{
public:
	void add(const Math::Vector3df& position);

	void estimate(const float searchRadius);

	std::vector<Math::Vector3df> getNormals() const { return normals; }

private:
	std::vector<Math::Vector3df> positions;
	std::vector<Math::Vector3df> normals;
};

	}
}