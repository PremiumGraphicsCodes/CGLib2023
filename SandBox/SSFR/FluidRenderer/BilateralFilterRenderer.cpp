#include "BilateralFilterRenderer.h"

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
		GLuint positionLoc;
	};
	VertexAttrLoc vaLoc;
}

void BilateralFilterRenderer::link()
{
	uniformLoc.tex = shader->findUniformLocation("tex");
	uniformLoc.width = shader->findUniformLocation("width");
	uniformLoc.height = shader->findUniformLocation("height");
	vaLoc.positionLoc = shader->findAttribLocation("position");
}

void BilateralFilterRenderer::render()
{
	/*
	const auto positions = ::toArray();

	shader->bind();

	TextureUnit texUnit(0, buffer.tex);

	Uniform texUniform(texLoc);
	texUniform.send(texUnit);

	VertexAttribute posAttr(positionLoc);
	posAttr.sendVertexAttribute2df(positions);

	shader->bindOutput("fragColor");

	glDrawArrays(GL_QUADS, 0, static_cast<GLsizei>(positions.size() / 2));

	shader->unbind();
	*/
}