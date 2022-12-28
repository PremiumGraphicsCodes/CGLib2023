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
	struct Seed
	{
		Math::Vector3df pos;
		Math::Vector3df velocity;
		float radius;
		float pressureCoe;
		float viscosityCoe;
		float mass;
	};

	MVPFluidEmitter();

	~MVPFluidEmitter();

	void emitParticle(const int timeStep);

	void clearParticles();

	void addSeed(const Seed& s) { this->seeds.push_back(s); }

	void setStartEnd(const int startStep, const int endStep) { this->startEndStep = std::make_pair(startStep, endStep); }

	void setInterval(const int interval) { this->interval = interval; }

	int getStartStep() const { return startEndStep.first; }

	int getEndStep() const { return startEndStep.second; }

	void clearSources() { this->seeds.clear(); }

	MVPVolumeParticle* create(const Math::Vector3df& position, const float radius, const float weight);

	std::list<MVPVolumeParticle*> getParticles() const override { return particles; }

	Math::Box3df getBoundingBox() const override;

private:
	std::vector<Seed> seeds;
	std::list<MVPVolumeParticle*> particles;
	std::pair<int, int> startEndStep;
	int interval;
};

	}
}