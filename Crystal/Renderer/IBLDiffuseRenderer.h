#pragma once

#include "CGLib/Shader/VertexBufferObject.h"
#include "CGLib/Shader/CubeMapTextureObject.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Renderer {

class IBLDiffuseRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Shader::CubeMapTextureObject* irradianceMapTex;
		Shader::VertexBufferObject* position;
		Shader::VertexBufferObject* normal;
		Math::Vector3df albedo;
		Math::Matrix4dd projectionMatrix;
		Math::Matrix4dd modelMatrix;
		Math::Matrix4dd viewMatrix;
		float metalic;
		float ao;
		Math::Vector3df eyePosition;
		std::vector<unsigned int> indices;
	};

	void link() override;

	void render() override;

	Buffer buffer;

private:
};

	}
}