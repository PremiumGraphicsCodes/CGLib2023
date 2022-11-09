#pragma once

#include <cmath>

namespace Crystal {
	namespace PC {

class GaussianFunc
{
public:
	GaussianFunc(const float a, const float b, const float c);

	float getWeight(const float x) const;

private:
	float a;
	float b;
	float c;
};

	}
}