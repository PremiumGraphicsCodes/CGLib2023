#pragma once

#include "../Graphics/Image.h"
#include "IGLObject.h"
#include "glew.h"

namespace Crystal {
	namespace Shader {

class ITextureObject : public IGLObject
{
public:
	virtual ~ITextureObject() = default;

	virtual void setParameter(const GLenum type, const GLuint value) = 0;

private:
	GLuint handle;
};

	}
}