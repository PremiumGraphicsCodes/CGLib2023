#include "GaussianFunc.h"
#include "CGLib/Math/pi.h"

using namespace Crystal::Math;
using namespace Crystal::PC;

GaussianFunc::GaussianFunc(const float a, const float b, const float c) :
	a(a),
	b(b),
	c(c)
{
}

float GaussianFunc::getWeight(const float x) const
{
	const auto power = (x - b) * (x - b) / (2.0f * c * c);
	return a * std::exp(power);
}

GaussianFunc GaussianFunc::createNormalDistributionFunc(const float mu, const float tau)
{
	const auto denomi = std::sqrt(2.0f * PI) * tau;
	const auto a = 1.0f / denomi;

	const auto b = mu;
	const auto c = tau;
	return GaussianFunc(a, b, c);
}

