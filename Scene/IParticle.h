#pragma once

#include "CGLib/Math/Vector3d.h"

namespace Crystal {
	namespace Scene {

class IParticle
{
public:
	virtual ~IParticle();

	virtual Math::Vector3df getPosition() const = 0;
};

	}
}