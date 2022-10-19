#include "SSAbsorptionRenderer.h"

#include "CGLib/Shader/TextureUnit.h"

using namespace Crystal::Shader;
using namespace Crystal::Renderer;

namespace {
	constexpr auto volumeTexLabel = "volumeTex";
	constexpr auto positionLabel = "position";
	constexpr auto fragColorLabel = "fragColor";
	
	GLuint volumeTexLoc = -1;
	GLuint positionLoc = -1;

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

void SSAbsorptionRenderer::link()
{
	volumeTexLoc = shader->findUniformLocation(::volumeTexLabel);
	positionLoc = shader->findAttribLocation(::positionLabel);
}

void SSAbsorptionRenderer::render()
{
	assert(GL_NO_ERROR == glGetError());

	const auto positions = ::toArray();

	shader->bind();

	TextureUnit texUnit(0, buffer.volumeTexture);

	Uniform texUniform(volumeTexLoc);
	texUniform.send(texUnit);

	VertexAttribute posAttr(positionLoc);
	posAttr.sendVertexAttribute2df(positions);

	shader->bindOutput(::fragColorLabel);

	glDrawArrays(GL_QUADS, 0, static_cast<GLsizei>(positions.size() / 2));

	shader->unbind();

	assert(GL_NO_ERROR == glGetError());

}
