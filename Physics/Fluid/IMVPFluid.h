#pragma once

#include "CGLib/Util/UnCopyable.h"
#include "CGLib/Math/Box3d.h"
#include <list>

namespace Crystal {
	namespace Physics {
		class MVPVolumeParticle;

class IMVPFluid : UnCopyable
{
public:
	~IMVPFluid() = default;

	virtual std::list<MVPVolumeParticle*> getParticles() const = 0;

	virtual Math::Box3df getBoundingBox() const = 0;
};

	}
}