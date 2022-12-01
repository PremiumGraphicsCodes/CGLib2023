#pragma once

#include "Crystal/Renderer/Renderer/IRenderer.h"
#include "CGLib/Shader/TextureObject.h"
#include "CGLib/Shader/CubeMapTextureObject.h"

namespace Crystal {
	namespace Renderer {

class SSReflectionRenderer : public IRenderer
{
public:
	struct Buffer {
		Math::Matrix4df projectionMatrix;
		Math::Vector3df eyePosition;
		Shader::TextureObject* depthTexture;
		Shader::TextureObject* normalTexture;
		Shader::CubeMapTextureObject* cubeMapTexture;
	};

	void link() override;

	void render() override;

	Buffer buffer;
};

	}
}