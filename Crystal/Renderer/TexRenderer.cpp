#include "TexRenderer.h"

#include "CGLib/Shader/ShaderBuilder.h"
#include "CGLib/Shader/VertexAttribute.h"

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

	GLuint texLoc;
	GLuint positionLoc;
}

void TexRenderer::link()
{
	texLoc = shader->findUniformLocation("texture");
	positionLoc = shader->findAttribLocation("position");
}

void TexRenderer::render()
{
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
}
