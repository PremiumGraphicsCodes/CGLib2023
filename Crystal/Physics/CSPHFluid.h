#pragma once

#include "CSPHParticle.h"
#include "CGLib/Util/UnCopyable.h"
#include "CGLib/Math/Box3d.h"

namespace Crystal {
	namespace Physics {

class CSPHFluid : private UnCopyable
{
public:
	CSPHFluid();

	~CSPHFluid() {}

	void addParticle(CSPHParticle* mp) { particles.push_back(mp); }

	std::list<CSPHParticle*> getParticles() const { return particles; }

	void clearParticles();

	Math::Box3df getBoundingBox() const;

	float getDensity() const { return density; }

	float getPressureCoe() const { return pressureCoe; }

	float getViscosityCoe() const { return viscosityCoe; }

	float getTensionCoe() const { return tensionCoe; }

	float getEffectLength() const { return effectLength; }

	bool isBoundary;

private:
	float tensionCoe;
	float viscosityCoe;
	float effectLength;
	float pressureCoe;
	float density;


private:
	std::list<CSPHParticle*> particles;
};

	}
}