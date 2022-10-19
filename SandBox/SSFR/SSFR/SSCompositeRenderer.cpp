#include "SSCompositeRenderer.h"

#include "CGLib/Shader/TextureUnit.h"

using namespace Crystal::Shader;
using namespace Crystal::Renderer;

namespace {
	constexpr auto DepthTextureLabel = "depthTexture";
	constexpr auto SurfaceTextureLabel = "surfaceTexture";
	constexpr auto ReflectionTextureLabel = "reflectionTexture";
	constexpr auto RefractionTextureLabel = "refractionTexture";
	constexpr auto AbsorptionTextureLabel = "absorptionTexture";
	constexpr auto BackGroundTextureLabel = "backgroundTexture";
	constexpr auto PositionLabel = "position";

	struct UniformLoc {
		GLuint depthTex;
		GLuint surfaceTex;
		GLuint reflectionTex;
		GLuint refractionTex;
		GLuint absorptionTex;
		GLuint bgTex;
	};

	struct VertexAttrLoc {
		GLuint position;
	};

	UniformLoc uniformLoc;
	VertexAttrLoc vaLoc;

	std::vector<float> toArray()
	{
		return{
			-1,  1,
			-1, -1,
			1, -1,
			1, 1
		};
	}
}

void SSCompositeRenderer::link()
{
	uniformLoc.depthTex = shader->findUniformLocation(::DepthTextureLabel);
	uniformLoc.surfaceTex = shader->findUniformLocation(::SurfaceTextureLabel);
	uniformLoc.reflectionTex = shader->findUniformLocation(::ReflectionTextureLabel);
	uniformLoc.refractionTex = shader->findUniformLocation(::RefractionTextureLabel);
	uniformLoc.absorptionTex = shader->findUniformLocation(::AbsorptionTextureLabel);
	uniformLoc.bgTex = shader->findUniformLocation(::BackGroundTextureLabel);
	vaLoc.position = shader->findAttribLocation(::PositionLabel);
}

void SSCompositeRenderer::render()
{
	assert(GL_NO_ERROR == glGetError());

	const auto positions = ::toArray();

	shader->bind();

	TextureUnit depthTexUnit(0, buffer.depthTexture);
	TextureUnit surfaceTexUnit(1, buffer.surfaceTexture);
	TextureUnit reflectionTexUnit(2, buffer.reflectionTexture);
	TextureUnit refractionTexUnit(3, buffer.refractionTexture);
	TextureUnit absorpTexUnit(4, buffer.absorptionTexture);
	TextureUnit bgTexUnit(5, buffer.backGroundTexture);

	Uniform depthTexUniform(uniformLoc.depthTex);
	Uniform surfaceTexUniform(uniformLoc.surfaceTex);
	Uniform reflectionTexUniform(uniformLoc.reflectionTex);
	Uniform refractionTexUniform(uniformLoc.refractionTex);
	Uniform absorpTexUniform(uniformLoc.absorptionTex);
	Uniform bgTexUniform(uniformLoc.bgTex);

	depthTexUniform.send(depthTexUnit);
	surfaceTexUniform.send(surfaceTexUnit);
	reflectionTexUniform.send(reflectionTexUnit);
	refractionTexUniform.send(refractionTexUnit);
	absorpTexUniform.send(absorpTexUnit);
	bgTexUniform.send(bgTexUnit);

	VertexAttribute posAttr(vaLoc.position);
	posAttr.sendVertexAttribute2df(positions);

	shader->bindOutput("fragColor");

	glDrawArrays(GL_QUADS, 0, static_cast<GLsizei>(positions.size() / 2));

	shader->unbind();

	assert(GL_NO_ERROR == glGetError());
}
