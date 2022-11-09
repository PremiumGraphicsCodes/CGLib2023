#include "GaussianFunc.h"

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
