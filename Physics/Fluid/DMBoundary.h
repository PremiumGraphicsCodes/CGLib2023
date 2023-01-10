#pragma once

#include "CGLib/Math/Vector3d.h"
#include "CGLib/Math/Sphere3d.h"

namespace Crystal {
	namespace Physics {
		class SPHKernel;

// DensityMap
class DMBoundary
{
public:
	float calculateWeight(const float signedDistance, const float r, const float restDensity, const SPHKernel& kernel);

	float calculateDensity(const float x, const float r, const float restDensity);

private:
	Math::Sphere3df boundary;
	//float r0;
};
	}
}