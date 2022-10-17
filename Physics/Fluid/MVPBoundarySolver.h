#pragma once

#include <vector>
#include <list>
#include <memory>

#include "CGLib/Math/Box3d.h"
#include "Crystal/Space/CompactSpaceHash.h"

namespace Crystal {
	namespace Physics {
		class MVPFluid;
		class MVPVolumeParticle;

class MVPBoundarySolver
{
public:
	MVPBoundarySolver() {}

	void addBoundary(MVPFluid* scene) { this->boundaries.push_back(scene); }

	void setup(const float effectLength);

	void clear() {
		boundaries.clear();
		csgBoundaries.clear();
		//		spaceHash.clear();
	}

	std::vector<int> findNeighbors(const Math::Vector3df& position);

	void add(const Math::Box3df& box) { this->csgBoundaries.push_back(box); }

	//MVPVolumeParticle* createGphost(const Math::Vector3df& p, MVPVolumeParticle* particle);

	//void createGphosts(MVPVolumeParticle* particle);

	void solvePressure(MVPVolumeParticle* particle, const double dt);

	void clearGphosts();

private:
	std::list<MVPFluid*> boundaries;
	std::unique_ptr<Space::CompactSpaceHash> spaceHash;
	std::list<Math::Box3df> csgBoundaries;
	std::list<MVPVolumeParticle*> ghosts;
	//MVPVolumeParticle* vp;
};

	}
}