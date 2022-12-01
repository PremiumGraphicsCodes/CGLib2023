#pragma once

//#include "VDBVolume.h"
#include "CGLib/Math/Sphere3d.h"
#include <vector>

namespace Crystal {
	namespace VDB {
		class VDBVolume;

class VDBToSpheres
{
public:
	void convert(const VDBVolume* src);

	std::vector<Math::Sphere3df> getSpheres() const { return spheres; }

private:
	std::vector<Math::Sphere3df> spheres;
};

	}
}