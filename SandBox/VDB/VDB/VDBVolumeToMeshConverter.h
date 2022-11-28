#pragma once

#include "VDBMesh.h"
#include "VDBVolume.h"

namespace Crystal {
	namespace VDB {

class VDBVolumeToMeshConverter
{
public:
	static VDBMesh* toMesh(const VDBVolume& volume, const double threshold, const double adaptivity);
};

	}
}