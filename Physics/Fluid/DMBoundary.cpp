#include "DMBoundary.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

float DMBoundary::calculateWeight(const SPHKernel& kernel)
{
	return 0.0f;
}

float DMBoundary::calculateDensity(const float x, const float r, const float restDensity)
{
	if (x >= r) {
		return 0.0f;
	}
	return restDensity * (1.0f - x / r);
}

float DMBoundary::calculatePhi(const Vector3df& v)
{
	return 0.0f;
}