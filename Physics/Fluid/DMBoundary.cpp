#include "DMBoundary.h"

#include "SPHKernel.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

float DMBoundary::calculateWeight(const float signedDistance, const float r, const float restDensity, const SPHKernel& kernel)
{
	return calculateDensity(signedDistance, r, restDensity ) * kernel.getCubicSpline(::fabs(signedDistance));
}

float DMBoundary::calculateDensity(const float x, const float r, const float restDensity)
{
	if (x >= r) {
		return 0.0f;
	}
	return restDensity * (1.0f - x / r);
}