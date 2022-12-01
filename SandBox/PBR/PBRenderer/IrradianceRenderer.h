#pragma once

#include "CGLib/Math/Matrix4d.h"
#include "CGLib/Shader/CubeMapTextureObject.h"
#include "Crystal/Renderer/Renderer/IRenderer.h"

namespace Crystal {
	namespace Renderer {

class IrradianceRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Shader::CubeMapTextureObject* cubeMapTex;
		Math::Matrix4df projectionMatrix;
		Math::Matrix4df viewMatrix;
	};

	void link() override;

	void render() override;

	Buffer buffer;

private:
};

	}
}