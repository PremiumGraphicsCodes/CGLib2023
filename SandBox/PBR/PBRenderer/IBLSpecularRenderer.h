#pragma once

#include "CGLib/Shader/ShaderObject.h"
#include "CGLib/Shader/VertexBufferObject.h"
#include "CGLib/Shader/CubeMapTextureObject.h"
#include "Crystal/Renderer/Renderer/IRenderer.h"

namespace Crystal {
	namespace Renderer {

class IBLSpecularRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Shader::CubeMapTextureObject* irradianceMapTex;
		Shader::CubeMapTextureObject* importanceMapTex;
		Shader::ITextureObject* brdfLutTex;
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

	IBLSpecularRenderer();

	void link() override;

	void render() override;

	Buffer buffer;

private:
};

	}
}