#pragma once

#include "../Graphics/Image.h"
#include "IGLObject.h"
#include "glew.h"

namespace Crystal {
	namespace Shader {

class TextureObject : public IGLObject
{
public:
	~TextureObject();

	void create() override;

	void remove() override;

	void send(const Graphics::Imageuc& image);

	void send(const Graphics::Imagef& image);

	void bind() const;

	void unbind() const;

	void setUnit(const GLint texUnit) { this->textureUnit = texUnit; }

	GLuint getHandle() const { return handle; }

private:
	GLuint handle;
	GLint textureUnit = 0;
};

	}
}