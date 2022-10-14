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

	//void addParticle(MVPVolumeParticle* mp);
	/*
{
	mp->setPressureCoe(this->pressureCoe);
	mp->setViscosityCoe(this->viscosityCoe);
	mp->setHeatDiffuseCue(this->heatDiffuseCoe);
	mp->setDragHeatCoe(this->dragHeatCoe);
	mp->setDragForceCoe(this->dragForceCoe);
	particles.push_back(mp);
}
*/

	std::list<MVPVolumeParticle*> getParticles() const { return particles; }

	void remove(MVPVolumeParticle* p) { particles.remove(p); }

	void removeDegeneratedVolumes();

	void removeExpired();

	void add(MVPVolumeParticle* p) { particles.push_back(p); }

	Math::Box3df getBoundingBox() const;

	void setPressureCoe(const float coe) { this->pressureCoe = coe; }

	float getPressure() const { return this->pressureCoe; }

	void setViscosityCoe(const float coe) { this->viscosityCoe = coe; }

	float getViscosityCoe() const { return this->viscosityCoe; }

	void setHeatDiffuseCoe(const float coe) { this->heatDiffuseCoe = coe; }

	float getHeatDiffuseCoe() const { return this->heatDiffuseCoe; }

	void setDragHeatCoe(const float c) { this->dragHeatCoe = c; }

	float getDragHeatCoe() const { return this->dragHeatCoe; }

	void setDragForceCoe(const float c) { this->dragForceCoe = c; }

	float getDragForceCoe() const { return this->dragForceCoe; }

	void setLifeLimit(const int limit) { this->lifeLimit = limit; }

	MVPVolumeParticle* create(const Math::Vector3df& position, const float radius, const float weight, const float temperature);

private:
	std::list<MVPVolumeParticle*> particles;
	float pressureCoe;
	float viscosityCoe;
	float heatDiffuseCoe;
	float dragHeatCoe;
	float dragForceCoe;
	int lifeLimit = -1;
};

	}
}