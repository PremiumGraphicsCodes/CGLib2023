#pragma once

#include "../Util/UnCopyable.h"
#include "glew.h"

namespace Crystal {
	namespace Shader {
		class TextureObject;

class TextureUnit : public UnCopyable
{
public:
	TextureUnit(const GLint unit, TextureObject* texture);

	~TextureUnit();

	void setTexture(TextureObject* texture) { this->texture = texture; }

	void bind() const;

	void unbind() const;

	GLuint getUnitNumber() const { return unit; }

private:
	GLint unit = 0;
	TextureObject* texture;
};

	}
}