#include "BilateralFilterRenderer.h"

#include "CGLib/Shader/Uniform.h"
#include "CGLib/Shader/TextureUnit.h"

using namespace Crystal::Shader;
using namespace Crystal::Renderer;

namespace {
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
		GLuint tex;
		GLuint width;
		GLuint height;
	};
	UniformLoc uniformLoc;

	struct VertexAttrLoc {
		GLuint position;
	};
	VertexAttrLoc vaLoc;
}

void BilateralFilterRenderer::link()
{
	uniformLoc.tex = shader->findUniformLocation("tex");
	uniformLoc.width = shader->findUniformLocation("width");
	uniformLoc.height = shader->findUniformLocation("height");
	vaLoc.position = shader->findAttribLocation("position");
}

void BilateralFilterRenderer::render()
{
	assert(GL_NO_ERROR == glGetError());

	const auto positions = ::toArray();

	shader->bind();

	TextureUnit texUnit(0, buffer.texture);

	Uniform texUniform(uniformLoc.tex);
	texUniform.send(texUnit);

	Uniform widthUniform(uniformLoc.width);
	widthUniform.send((float)buffer.texture->getWidth());

	Uniform heightUniform(uniformLoc.height);
	heightUniform.send((float)buffer.texture->getHeight());

	VertexAttribute posAttr(vaLoc.position);
	posAttr.sendVertexAttribute2df(positions);

	shader->bindOutput("fragColor");

	glDrawArrays(GL_QUADS, 0, static_cast<GLsizei>(positions.size() / 2));

	shader->unbind();

	assert(GL_NO_ERROR == glGetError());

}