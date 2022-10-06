#pragma once

#include "SPHKernel.h"
#include "CGLib/Math/Box3d.h"
#include "CGLib/Util/UnCopyable.h"
#include <vector>

namespace Crystal {
	namespace Physics {
		class CSPHFluid;

class CSPHSolver : private UnCopyable
{
public:
	CSPHSolver()
	{}

	void add(CSPHFluid* particle) { this->fluids.push_back(particle); }

	void simulate(const float timeStep);

	void setExternalForce(const Math::Vector3df& force) { this->externalForce = force; }

	//std::vector<CSPHParticle*> getParticles() const { return particles; }

	void setBoundary(const Math::Box3df& boundary) { this->boundary = boundary; }

	void setEffectLenth(const float length) { this->effectLength = length; }

private:
	float effectLength = 1.25f;
	//SPHKernel kernel;
	std::vector<CSPHFluid*> fluids;
	Math::Vector3df externalForce;
	Math::Box3df boundary;
};

	}
}