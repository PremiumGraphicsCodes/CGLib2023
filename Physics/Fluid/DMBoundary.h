#pragma once

#include "CGLib/Math/Vector3d.h"
#include "CGLib/Math/Box3d.h"

namespace Crystal {
	namespace Physics {
		class SPHKernel;

// DensityMap
class DMBoundary
{
public:
	void addBox(const Math::Box3df& box) { this->boundary = box; }

	float calculateWeight(const Math::Vector3df& position, const float r, const float restDensity, const SPHKernel& kernel);

	float calculateWeight(const float signedDistance, const float r, const float restDensity, const SPHKernel& kernel);

	float calculateDensity(const float x, const float r, const float restDensity);

private:
	Math::Box3df boundary;
	//Math::Sphere3df boundary;
	//float r0;
};
	}
}