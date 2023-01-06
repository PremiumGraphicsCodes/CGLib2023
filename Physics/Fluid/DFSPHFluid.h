#pragma once

#include "DFSPHParticle.h"
#include "CGLib/Util/UnCopyable.h"
#include "CGLib/Math/Box3d.h"

#include <memory>
#include <list>

namespace Crystal {
	namespace Physics {

class DFSPHFluid : private UnCopyable
{
public:
	DFSPHFluid();

	~DFSPHFluid() {}

	void addParticle(std::unique_ptr<DFSPHParticle>&& mp) { particles.push_back(std::move(mp)); }

	const std::list<std::unique_ptr<DFSPHParticle>>& getParticles() const { return particles; }

	Math::Box3df getBoundingBox() const;

	float getDensity() const { return density; }

	float getViscosityCoe() const { return viscosityCoe; }

	float viscosityCoe;
	float effectLength;
	float pressureCoe;
	float density;

private:
	std::list<std::unique_ptr<DFSPHParticle>> particles;
};

	}
}