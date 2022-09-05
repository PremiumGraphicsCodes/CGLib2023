#pragma once

#include "IScreenShader.h"

#include "CGLib/Shader/FrameBufferObject.h"
#include "CGLib/Shader/RenderBufferObject.h"

#include "../Renderer/CubeMapRenderer.h"
#include "../Renderer/IrradianceRenderer.h"
#include "../Renderer/IBLDiffuseRenderer.h"
#include "../Renderer/IBLSpecularRenderer.h"
#include "../Renderer/BRDFLUTRenderer.h"
#include "../Renderer/ImportanceRenderer.h"
#include "../Renderer/TexRenderer.h"
#include "../Renderer/SkyBoxRenderer.h"

namespace Crystal {
	namespace Renderer {

class IBLShader : public IScreenShader
{
public:
	void build() override;

	void render(const Graphics::Camera& camera, const int width, const int height) override;

private:
	struct Renderers
	{
		Renderer::CubeMapRenderer cubeMap;
		Renderer::IrradianceRenderer irradiance;
		Renderer::IBLDiffuseRenderer diffuse;
		Renderer::IBLSpecularRenderer specular;
		Renderer::BRDFLUTRenderer brdfLut;
		Renderer::ImportanceRenderer importance;
		Renderer::SkyBoxRenderer skyBox;
	};

	struct Textures
	{
		Shader::CubeMapTextureObject cubeMapTex;
		Shader::CubeMapTextureObject irradianceTex;
		Shader::CubeMapTextureObject importanceTex;
		Shader::TextureObject hdrTex;
		Shader::TextureObject brdfLutTex;
	};

	struct Buffers
	{
		Shader::FrameBufferObject fbo;
		Shader::RenderBufferObject rbo;
		Shader::VertexBufferObject positionVBO;
		Shader::VertexBufferObject normalVBO;
	};

	Renderers renderers;
	Textures textures;
	Buffers buffers;

	//Graphics::Buffer3d<float> positions;
	//Graphics::Buffer3d<float> normals;
	std::vector<unsigned int> indices;

};

	}
}