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

	const std::string vsSource = R"(
#version 150
in vec2 position;
out vec2 texCoord;
void main(void) {
	texCoord = (position + vec2(1.0,1.0))/2.0;
	gl_Position = vec4(position, 0.0, 1.0);
}
)";

	const std::string fsSource = R"(
#version 150
uniform sampler2D texture;
in vec2 texCoord;
out vec4 fragColor;
void main(void) {
	fragColor = texture2D(texture, texCoord);
}
)";
}

void TexRenderer::build()
{
	ShaderBuilder builder;
	builder.build(vsSource, fsSource);
	this->shader = builder.getShader();

}


void TexRenderer::render()
{
	/*
	const auto positions = ::toArray();

	//glEnable(GL_DEPTH_TEST);

	shader->bind();
	//glUseProgram(shader->getHandle());

	buffer.tex->bind(0);

	//glUniform1i(shader->getUniformLocation("texture"), 0);
	shader->sendUniform("texture", texture, 0);

	shader->sendVertexAttribute2df("position", positions);

	glEnableVertexAttribArray(0);
	glDrawArrays(GL_QUADS, 0, static_cast<GLsizei>(positions.size() / 2));
	glDisableVertexAttribArray(0);

	shader->bindOutput("fragColor");

	texture.unbind();
	//glDisable(GL_DEPTH_TEST);

	shader->unbind();
	*/
}
