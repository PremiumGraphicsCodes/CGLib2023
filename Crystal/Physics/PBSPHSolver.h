#pragma once

#include <vector>

#include "CGLib/Math/Vector3d.h"
#include "CGLib/Math/Box3d.h"
#include "CGLib/Util/UnCopyable.h"

namespace Crystal {
	namespace Physics {

class PBSPHParticle;
class PBSPHFluid;

class PBSPHSolver : private UnCopyable
{
public:
	PBSPHSolver();

	void clear() { this->fluids.clear(); }

	void add(PBSPHFluid* fluid) { this->fluids.push_back(fluid); }

	void simulate(const float dt, const int maxIter);

	void setBoundary(const Math::Box3df& boundary) { this->boundary = boundary; }

	void setExternalForce(const Math::Vector3df& force) { this->externalForce = force; }

	void setTimeStep(const float dt) { this->maxTimeStep = dt; }

private:
	std::vector<PBSPHFluid*> fluids;
	Math::Box3df boundary;
	Math::Vector3df externalForce;
	float maxTimeStep;
	//float effectLength;

	float calculateTimeStep(const std::vector<PBSPHParticle*>& particles);

		};

	}
}