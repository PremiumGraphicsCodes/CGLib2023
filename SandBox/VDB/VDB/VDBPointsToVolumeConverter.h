#pragma once

#include <vector>
#include <memory>

#include "VDBPoints.h"
#include "VDBVolume.h"

namespace Crystal {
	namespace VDB {

class VDBPoints;
class VDBVolume;

class SmoothVolumeConverter
{
public:
	std::vector<VDBVolume*> build(VDBPoints* vdbParticles, const float particleRadius, const float cellLength, const std::vector<std::string>& floatNames);

private:
};

	}
}