#include "TexRenderer.h"

#include "../Shader/ShaderBuilder.h"
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

	Uniform texLoc;
	VertexAttribute positionAttr;
}

void TexRenderer::link()
{
	texLoc = shader->findUniformLocation("texture");
	positionAttr = shader->findAttribLocation("position");
}


void TexRenderer::render()
{
	const auto positions = ::toArray();

	shader->bind();

	texLoc.send(buffer.tex, 0);

	positionAttr.sendVertexAttribute2df(positions);
	shader->bindOutput("fragColor");

	positionAttr.bind();

	glDrawArrays(GL_QUADS, 0, static_cast<GLsizei>(positions.size() / 2));
	
	positionAttr.unbind();

	shader->unbind();
}
