#include "SSRefractionRenderer.h"

#include "CGLib/Shader/TextureUnit.h"

using namespace Crystal::Shader;
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
	uniformLoc.eyePosition = shader->findUniformLocation(::eyePositionLabel);
	uniformLoc.depthTex = shader->findUniformLocation(::depthTexLabel);
	uniformLoc.normalTex = shader->findUniformLocation(::normalTexLabel);
	uniformLoc.cubeMapTex = shader->findUniformLocation(::cubeMapTexLabel);

	vaLoc.position = shader->findAttribLocation(::positionLabel);
}

void SSRefractionRenderer::render()
{
	assert(GL_NO_ERROR == glGetError());

	const auto positions = ::toArray();

	shader->bind();

	TextureUnit depthTexUnit(0, buffer.depthTexture);
	Uniform depthTexUniform(uniformLoc.depthTex);
	depthTexUniform.send(depthTexUnit);

	TextureUnit normalTexUnit(1, buffer.normalTexture);
	Uniform normalTexUniform(uniformLoc.normalTex);
	normalTexUniform.send(normalTexUnit);

	TextureUnit cubeMapTexUnit(2, buffer.cubeMapTexture);
	Uniform cubeMapTexUniform(uniformLoc.cubeMapTex);
	cubeMapTexUniform.send(cubeMapTexUnit);

	Uniform projectionMatrix(uniformLoc.projectionMatrix);
	projectionMatrix.send(buffer.projectionMatrix);

	Uniform eyePosition(uniformLoc.eyePosition);
	eyePosition.send(buffer.eyePosition);

	VertexAttribute posAttr(vaLoc.position);
	posAttr.sendVertexAttribute2df(positions);

	shader->bindOutput("fragColor");

	glDrawArrays(GL_QUADS, 0, static_cast<GLsizei>(positions.size() / 2));

	shader->unbind();

	assert(GL_NO_ERROR == glGetError());
}
