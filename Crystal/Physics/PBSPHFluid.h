#pragma once

#include "CGLib/Util/UnCopyable.h"
#include "CGLib/Math/Box3d.h"
#include "SPHKernel.h"
#include <list>

namespace Crystal {
	namespace Physics {
		class PBSPHParticle;

class PBFluid : private UnCopyable
{
public:
	PBFluid();

	~PBFluid();

	void addParticle(PBSPHParticle* mp) { particles.push_back(mp); }

	std::list<PBSPHParticle*> getParticles() const { return particles; }

	Math::Box3df getBoundingBox() const;

	SPHKernel* getKernel() { return &kernel; }

	float getRestDensity() const { return restDensity; }

	void setEffectLength(const float effectLength);

	void setRestDensity(const float restDensity);

	void setStiffness(const float s) { this->stiffness = s; }

	float getStiffness() const { return stiffness; }

	void setVicsosity(const float v) { this->viscosity = v; }

	float getViscosity() const { return viscosity; }

	bool isBoundary() const { return _isBoundary; }

	void setIsBoundary(const bool b) { _isBoundary = b; }

private:
	std::list<PBSPHParticle*> particles;
	SPHKernel kernel;
	float restDensity;
	float stiffness;
	float viscosity;
	bool _isBoundary;
};

	}
}