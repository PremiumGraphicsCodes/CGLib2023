#pragma once

#include "CGLib/Math/Vector3d.h"
#include "CGLib/Math/Box3d.h"
#include "Crystal/Space/Space/CompactSpaceHash.h"

namespace Crystal {
	namespace Physics {
		class PBSPHParticle;
		class PBSPHBoundaryParticle;

class PBSPHBoundarySolver
{
public:
	PBSPHBoundarySolver() {};

	explicit PBSPHBoundarySolver(const Math::Box3df& boundary);

	void addDX(const std::vector<PBSPHParticle*>& particles, const float dt);

	void calculatePressure(const std::vector<PBSPHParticle*>& particles);

	void calculateViscosity(const std::vector<PBSPHParticle*>& particles);

private:
	bool isBoundary(PBSPHParticle* particle);

	//Math::Vector3df getBoundaryPosition(PBSPHParticle* particle);

	Math::Vector3df getOverVector(const Math::Vector3df& position);

	float getOverX(const float x);
	float getOverY(const float y);
	float getOverZ(const float z);

	const Math::Box3df boundary;
};

	}
}