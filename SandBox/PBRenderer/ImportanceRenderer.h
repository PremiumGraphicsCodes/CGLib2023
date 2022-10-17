#pragma once

#include "Crystal/Renderer/IRenderer.h"

#include "CGLib/Shader/CubeMapTextureObject.h"

namespace Crystal {
	namespace Renderer {

class ImportanceRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Shader::CubeMapTextureObject* evnMapTex;
		float roughness;
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