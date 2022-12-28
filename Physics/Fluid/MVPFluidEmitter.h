#pragma once

#include "CGLib/Math/Sphere3d.h"
#include "IMVPFluid.h"
#include <vector>
#include <list>

namespace Crystal {
	namespace Physics {
		class MVPVolumeParticle;

class MVPFluidEmitter : public IMVPFluid
{
public:
	MVPFluidEmitter();

	~MVPFluidEmitter();

	void emitParticle(const int timeStep);

	void clearParticles();

	void addSource(const Math::Sphere3df& s) { this->sourcePositions.push_back(s); }

	void setStartEnd(const int startStep, const int endStep) { this->startEndStep = std::make_pair(startStep, endStep); }

	void setInterval(const int interval) { this->interval = interval; }

	int getStartStep() const { return startEndStep.first; }

	int getEndStep() const { return startEndStep.second; }

	void setInitialVelocity(const Math::Vector3df& velocity) { this->initialVelocity = velocity; }

	void clearSources() { this->sourcePositions.clear(); }

	MVPVolumeParticle* create(const Math::Vector3df& position, const float radius, const float weight);

	std::list<MVPVolumeParticle*> getParticles() const override { return particles; }

	Math::Box3df getBoundingBox() const override;

private:
	std::vector<Math::Sphere3df> sourcePositions;
	std::list<MVPVolumeParticle*> particles;
	Math::Vector3df initialVelocity;
	std::pair<int, int> startEndStep;
	int interval;
};

	}
}