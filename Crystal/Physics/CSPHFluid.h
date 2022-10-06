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

	void addParticle(std::unique_ptr<CSPHParticle> mp) { particles.push_back(std::move(mp)); }

	const std::list<std::unique_ptr<CSPHParticle>>& getParticles() const { return particles; }

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
	std::list<std::unique_ptr<CSPHParticle>> particles;
};

	}
}