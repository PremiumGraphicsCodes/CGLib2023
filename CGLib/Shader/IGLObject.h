#pragma once

#include "../Util/UnCopyable.h"
#include "glew.h"

namespace Crystal {
	namespace Shader {

class IGLObject : private UnCopyable
{
public:
	IGLObject() {};

	virtual ~IGLObject() {};

	virtual void create() = 0;

	virtual void remove() = 0;

	virtual void bind() const = 0;

	virtual void unbind() const = 0;

	virtual GLuint getHandle() const = 0;
};
	}
}