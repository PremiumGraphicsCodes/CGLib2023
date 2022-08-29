#pragma once

#include "../Util/UnCopyable.h"
#include "ITextureObject.h"

namespace Crystal {
	namespace Shader {
		class ITextureObject;

class TextureUnit : public UnCopyable
{
public:
	TextureUnit(const GLint unit, ITextureObject* texture);

	~TextureUnit();

	//void setTexture(ITextureObject* texture) { this->texture = texture; }

	void bind() const;

	void unbind() const;

	GLuint getUnitNumber() const { return unit; }

private:
	GLint unit = 0;
	ITextureObject* texture;
};

	}
}