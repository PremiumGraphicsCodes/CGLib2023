#include "SSRefractionRenderer.h"

using namespace Crystal::Renderer;

namespace {
	constexpr auto projectionMatrixLabel = "projectionMatrix";
	constexpr auto eyePositionLabel = "eyePosition";
	constexpr auto depthTexLabel = "depthTex";
	constexpr auto normalTexLabel = "normalTex";
	constexpr auto cubeMapTexLabel = "cubeMapTex";
	constexpr auto positionLabel = "position";
	constexpr auto fragColorLabel = "fragColor";

	std::vector<float> toArray()
	{
		return{
			-1,  1,
			-1, -1,
			1, -1,
			1, 1
		};
	}

	struct UniformLoc
	{
		GLuint projectionMatrix;
		GLuint eyePosition;
		GLuint depthTex;
		GLuint normalTex;
		GLuint cubeMapTex;
	};
	UniformLoc uniformLoc;

	struct VertexAttrLoc
	{
		GLuint position;
	};
	VertexAttrLoc vaLoc;
}

void SSRefractionRenderer::link()
{
	uniformLoc.projectionMatrix = shader->findUniformLocation(::projectionMatrixLabel);
}

void SSRefractionRenderer::render()
{

}
