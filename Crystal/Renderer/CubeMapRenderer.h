#pragma once

#include "IRenderer.h"

#include "CGLib/Math/Matrix4d.h"
#include "CGLib/Shader/TextureObject.h"

namespace Crystal {
	namespace Renderer {

class CubeMapRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Math::Matrix4df projectionMatrix;
		Math::Matrix4df viewMatrix;
		Shader::TextureObject* texture;
	};

	void link() override;

	void render() override;

	Buffer buffer;

private:
};

	}
}