#pragma once

#include "IScreenShader.h"

#include "CGLib/Shader/FrameBufferObject.h"
#include "../Renderer/DFAlbedoRenderer.h"
#include "../Renderer/DFGeometryRenderer.h"

namespace Crystal {
	namespace Renderer {

class DFPolygonShader : public IScreenShader
{
public:
	void build() override;

	void render(const Graphics::Camera& camera, const int width, const int height) override;

private:
	Renderer::DFAlbedoRenderer albedoRenderer;
	Renderer::DFGeometryRenderer gRenderer;
	//Renderer::DFLightRenderer lightRenderer;

	Shader::TextureObject colorTexture;
	Shader::TextureObject polygonTexture;
	Shader::TextureObject positionTexture;
	Shader::TextureObject normalTexture;
	Shader::TextureObject shadedTexture;
	Shader::VertexBufferObject positions;
	Shader::VertexBufferObject texCoords;
	Shader::VertexBufferObject normals;

	Shader::FrameBufferObject fbo;

};

	}
}