#pragma once

#include <list>
#include "CGLib/Math/Box3d.h"

namespace Crystal {
	namespace Physics {
		class MVPVolumeParticle;

class MVPFluid
{
public:
	MVPFluid();

	~MVPFluid();

	std::list<MVPVolumeParticle*> getParticles() const { return particles; }

	void remove(MVPVolumeParticle* p) { particles.remove(p); }

	void removeDegeneratedVolumes();

	void add(MVPVolumeParticle* p) { particles.push_back(p); }

	Math::Box3df getBoundingBox() const;

	//void setPressureCoe(const float coe) { this->pressureCoe = coe; }

	//float getPressure() const { return this->pressureCoe; }

	//void setViscosityCoe(const float coe) { this->viscosityCoe = coe; }

	//float getViscosityCoe() const { return this->viscosityCoe; }

	void setLifeLimit(const int limit) { this->lifeLimit = limit; }

	MVPVolumeParticle* create(const Math::Vector3df& position, const float radius, const float weight);

private:
	std::list<MVPVolumeParticle*> particles;
	//float pressureCoe;
	//float viscosityCoe;
	int lifeLimit = -1;
};

	}
}