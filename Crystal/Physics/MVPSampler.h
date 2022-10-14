#pragma once

#include <list>

namespace Crystal {
	namespace Physics {
		class MVPFluid;

class MVPSampler
{
public:
	void merge(const std::list<MVPFluid*>& fluids, const double searchRadius);

	void split(const std::list<MVPFluid*>& fluids);
};

	}
}