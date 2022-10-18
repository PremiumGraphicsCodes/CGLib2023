#pragma once

#include "IScreenShader.h"

#include "CGLib/Shader/FrameBufferObject.h"
#include "CGLib/Shader/RenderBufferObject.h"

#include "../PBRenderer/CubeMapRenderer.h"
#include "../PBRenderer/IrradianceRenderer.h"
#include "../PBRenderer/IBLDiffuseRenderer.h"
#include "../PBRenderer/IBLSpecularRenderer.h"
#include "../PBRenderer/BRDFLUTRenderer.h"
#include "../PBRenderer/ImportanceRenderer.h"
#include "Crystal/Renderer/TexRenderer.h"
#include "Crystal/Renderer/SkyBoxRenderer.h"

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
		Renderer::TexRenderer tex;
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
		Shader::RenderBufferObject depth;
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