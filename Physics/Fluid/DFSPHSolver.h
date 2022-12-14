#pragma once

#include <vector>

#include "CGLib/Math/Vector3d.h"
#include "CGLib/Math/Box3d.h"

namespace Crystal {
	namespace Physics {

class DFSPHParticle;
class DFSPHFluid;

class DFSPHSolver
{
public:
	DFSPHSolver();

	void add(DFSPHFluid* fluid) { this->fluids.push_back(fluid); }

	void simulate(const float searchRadius, const int maxIter);

	void setBoundary(const Math::Box3df& boundary) { this->boundary = boundary; }

	void setExternalForce(const Math::Vector3df& force) { this->externalForce = force; }

	//std::vector<PBSPHParticle*> getParticles() const { return particles; }

	void setTimeStep(const float dt) { this->maxTimeStep = dt; }

private:
	std::vector<DFSPHFluid*> fluids;
	Math::Box3df boundary;
	Math::Vector3df externalForce;
	float maxTimeStep;

private:
	void correctDivergenceError(const std::vector<DFSPHParticle*>& particles, const float dt);

	void correctDensityError(const std::vector<DFSPHParticle*>& particles, const float dt);

	float calculateTimeStep(const std::vector<DFSPHParticle*>& particles);

	float calculateAverageDensity(const std::vector<DFSPHParticle*>& particles);

	float calculateAverageDpDt(const std::vector<DFSPHParticle*>& particles);
};

	}
}