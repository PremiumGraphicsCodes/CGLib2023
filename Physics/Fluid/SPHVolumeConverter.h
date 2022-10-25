#pragma once

#include <vector>
#include <memory>

#include "SPHSurfaceParticle.h"

#include "Crystal/Space/SparseVolume.h"

namespace Crystal {
	namespace Physics {

class SPHVolumeConverter
{
public:
	std::unique_ptr<Space::SparseVolumef> buildIsotoropic(const std::vector<Math::Vector3dd>& positions, const float particleRadius, const float cellLength);

	std::unique_ptr<Space::SparseVolumef> buildAnisotoropic(const std::vector<Math::Vector3dd>& positions, const float particleRadius, const float cellLength);

	const std::vector<std::unique_ptr<SPHSurfaceParticle>>& getParticles() const { return particles; }

	//std::vector < Shape::Volume<double>* > getVolumes() { return volumes; }

private:
	std::unique_ptr<Space::SparseVolumef> createSparseVolume(const std::vector<Math::Vector3dd>& particles, const float cellLength);

	void calculateDensity(const float searchRadius);

	void calculateAnisotropy(const float searchRadius);

	std::vector<std::unique_ptr<SPHSurfaceParticle>> particles;
};

	}
}