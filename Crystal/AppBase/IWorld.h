#pragma once

#include "CGLib/Util/UnCopyable.h"

namespace Crystal {
	namespace UI {

class IWorld : private UnCopyable
{
public:
	virtual ~IWorld() = default;
};
	}
}