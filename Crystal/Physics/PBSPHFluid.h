#pragma once

#include "CGLib/Util/UnCopyable.h"
#include "CGLib/Math/Box3d.h"
#include "SPHKernel.h"
#include "PBSPHParticle.h"
#include <list>
#include <memory>

namespace Crystal {
	namespace Physics {

class PBSPHFluid : private UnCopyable
{
public:
	PBSPHFluid();

	~PBSPHFluid();

	void addParticle(std::unique_ptr<PBSPHParticle> mp) { particles.push_back(std::move(mp)); }

	std::list<std::unique_ptr<PBSPHParticle>>& getParticles() { return particles; }

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
	std::list<std::unique_ptr<PBSPHParticle>> particles;
	SPHKernel kernel;
	float restDensity;
	float stiffness;
	float viscosity;
	bool _isBoundary;
};

	}
}