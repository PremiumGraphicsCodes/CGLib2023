#include "SSNormalRenderer.h"

#include "CGLib/Shader/TextureUnit.h"

using namespace Crystal::Shader;
using namespace Crystal::Renderer;

namespace {
	constexpr auto projectionMatrixLabel = "projectionMatrix";
	constexpr auto depthTexLabel = "depthTex";
	constexpr auto texelSizeWLabel = "texelSizeW";
	constexpr auto texelSizeHLabel = "texelSizeH";
	constexpr auto positionLabel = "position";

	std::vector<float> toArray()
	{
		return{
			-1,  1,
			-1, -1,
			1, -1,
			1, 1
		};
	}

	struct UniformLoc {
		GLuint projectionMatrix;
		GLuint depthTex;
		GLuint texelSizeW;
		GLuint texelSizeH;
	};
	UniformLoc uniformLoc;

	struct VertexAttrLoc {
		GLuint position;
	};
	VertexAttrLoc vaLoc;
}


void SSNormalRenderer::link()
{
	uniformLoc.projectionMatrix = shader->findUniformLocation(::projectionMatrixLabel);
	uniformLoc.depthTex = shader->findUniformLocation(::depthTexLabel);
	uniformLoc.texelSizeW = shader->findUniformLocation(::texelSizeWLabel);
	uniformLoc.texelSizeH = shader->findUniformLocation(::texelSizeHLabel);

	vaLoc.position = shader->findAttribLocation(::positionLabel);
}

void SSNormalRenderer::render()
{
	assert(GL_NO_ERROR == glGetError());

	const auto positions = ::toArray();

	shader->bind();

	TextureUnit texUnit(0, buffer.depthTexture);

	Uniform texUniform(uniformLoc.depthTex);
	texUniform.send(texUnit);

	Uniform projectionMatrix(uniformLoc.projectionMatrix);
	projectionMatrix.send(buffer.projectionMatrix);

	Uniform widthUniform(uniformLoc.texelSizeW);
	widthUniform.send(1.0f / (float)buffer.depthTexture->getWidth());

	Uniform heightUniform(uniformLoc.texelSizeH);
	heightUniform.send(1.0f / (float)buffer.depthTexture->getHeight());

	VertexAttribute posAttr(vaLoc.position);
	posAttr.sendVertexAttribute2df(positions);

	shader->bindOutput("fragColor");

	glDrawArrays(GL_QUADS, 0, static_cast<GLsizei>(positions.size() / 2));

	shader->unbind();

	assert(GL_NO_ERROR == glGetError());
}
