#pragma once

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {

class IGLObject : private UnCopyable
{
public:
	IGLObject() {};

	virtual ~IGLObject() {};

	virtual void create() = 0;

	virtual void remove() = 0;
};
	}
}