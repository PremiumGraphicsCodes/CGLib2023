#pragma once

#//include "../Graphics/Imagef.h"
#include "../Graphics/Image.h"
#include "IGLObject.h"

#include "glew.h"

#include <array>

namespace Crystal {
	namespace Shader {

class CubeMapTextureObject : public IGLObject
{
public:
	void create();

	void remove() override;

	void send(const std::array<Graphics::Imagef, 6>& images);

	void send(const std::array<Graphics::Imageuc, 6>& images);

	void setPositiveX(const Graphics::Imagef& image);

	//void setPositiveX(const Graphics::Image& image);

	void setNegativeX(const Graphics::Imagef& image);

	//void setNegativeX(const Graphics::Image& image);

	void setPositiveY(const Graphics::Imagef& image);

	//void setPositiveY(const Graphics::Image& image);

	void setNegativeY(const Graphics::Imagef& image);

	//void setNegativeY(const Graphics::Image& image);

	void setPositiveZ(const Graphics::Imagef& image);

	//void setPositiveZ(const Graphics::Image& image);

	void setNegativeZ(const Graphics::Imagef& image);

	//void setNegativeZ(const Graphics::Image& image);

	void bind() const;// override;

	void unbind() const; //override;

private:
	GLuint handle;
};

	}
}