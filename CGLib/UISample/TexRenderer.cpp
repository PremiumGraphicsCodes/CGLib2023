#include "TexRenderer.h"

#include "../Shader/ShaderBuilder.h"
#include "../Shader/TextureUnit.h"
#include "../Shader/VertexAttribute.h"

using namespace Crystal::Shader;
using namespace Crystal::UI;

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
	GLuint posLoc;
}

void TexRenderer::link()
{
	texLoc = shader->findUniformLocation("texture");
	posLoc = shader->findAttribLocation("position");
}


void TexRenderer::render()
{
	const auto positions = ::toArray();

	//glEnable(GL_DEPTH_TEST);

	shader->bind();

	TextureUnit texUnit(0, buffer.tex);
	texUnit.bind();

	shader->sendUniform(texLoc, 0);

	VertexAttribute posAttr(posLoc);
	posAttr.sendVertexAttribute2df(positions);
	shader->bindOutput("fragColor");

	posAttr.enableVertexAttribute();

	glDrawArrays(GL_QUADS, 0, static_cast<GLsizei>(positions.size() / 2));
	
	posAttr.disableVertexAttribute();

	texUnit.unbind();

	//glDisable(GL_DEPTH_TEST);

	shader->unbind();
}
