#pragma once

#include <list>
#include "CGLib/Math/Box3d.h"
#include "IMVPFluid.h"

namespace Crystal {
	namespace Physics {
		class MVPVolumeParticle;

class MVPFluid : public IMVPFluid
{
public:
	MVPFluid();

	~MVPFluid();

	std::list<MVPVolumeParticle*> getParticles() const override { return particles; }

	void remove(MVPVolumeParticle* p) { particles.remove(p); }

	void removeDegeneratedVolumes();

	void add(MVPVolumeParticle* p) { particles.push_back(p); }

	Math::Box3df getBoundingBox() const override;

	void setLifeLimit(const int limit) { this->lifeLimit = limit; }

	MVPVolumeParticle* create(const Math::Vector3df& position, const float radius, const float weight);

private:
	std::list<MVPVolumeParticle*> particles;
	int lifeLimit = -1;
};

	}
}