#pragma once

#include "glew.h"

namespace Crystal {
	namespace Shader {

class TextureUnit
{
public:
	explicit TextureUnit(const GLint number);

	void bind();

	void unbind();

	GLint get() const { return number; }

private:
	GLint number;
};
	}
}