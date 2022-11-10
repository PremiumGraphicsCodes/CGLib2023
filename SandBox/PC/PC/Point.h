#pragma once

#include "CGLib/Math/Vector3d.h"

namespace Crystal {
	namespace PC {

class IPoint
{
public:
	virtual ~IPoint() = default;

	virtual Math::Vector3df getPosition() const = 0;
};



	}
}