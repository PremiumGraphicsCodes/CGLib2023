#pragma once

namespace Crystal {
	namespace VDB {
		class VDBVolume;
		class VDBPoints;

class VDBVolumeToPointsConverter
{
public:
	static VDBPoints* toPoints(const VDBVolume& volume);

private:
};

	}
}