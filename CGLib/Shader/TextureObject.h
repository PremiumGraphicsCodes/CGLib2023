#pragma once

#include "../Graphics/Image.h"
#include "ITextureObject.h"
#include "glew.h"

namespace Crystal {
	namespace Shader {

class TextureObject : public ITextureObject
{
public:
	~TextureObject();

	void create() override;

	void remove() override;

	void send(const Graphics::Imageuc& image);

	void send(const Graphics::Imagef& image);

	void setParameter(const GLenum type, const GLuint value) override;

	void bind() const override;

	void unbind() const override;

	int getWidth() { return width; }

	int getHeight() { return height; }

	Graphics::Imageuc toImageuc() const;

private:
	int width;
	int height;
};

	}
}