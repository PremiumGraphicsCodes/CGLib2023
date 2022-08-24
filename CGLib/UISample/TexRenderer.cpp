#include "TexRenderer.h"

#include "../Shader/ShaderBuilder.h"

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

void TexRenderer::build()
{
	texLoc = shader->findUniformLocation("texture");
	posLoc = shader->findAttribLocation("position");
}


void TexRenderer::render()
{
	const auto positions = ::toArray();

	//glEnable(GL_DEPTH_TEST);

	shader->bind();
	//glUseProgram(shader->getHandle());

	buffer.tex->setUnit(0);

	buffer.tex->bind();

	shader->sendUniform(texLoc, 0);

	shader->sendVertexAttribute2df(posLoc, positions);
	shader->bindOutput("fragColor");

	glEnableVertexAttribArray(0);
	glDrawArrays(GL_QUADS, 0, static_cast<GLsizei>(positions.size() / 2));
	glDisableVertexAttribArray(0);


	buffer.tex->unbind();

	//glDisable(GL_DEPTH_TEST);

	shader->unbind();
}
