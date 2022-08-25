#include "PointRenderer.h"

#include "../Shader/ShaderBuilder.h"

using namespace Crystal::Shader;
using namespace Crystal::UI;

namespace {
	constexpr auto positionLabel = "position";
	constexpr auto colorLabel = "color";
	constexpr auto sizeLabel = "pointSize";
	constexpr auto projectionMatrixLabel = "projectionMatrix";
	constexpr auto modelViewMatrixLabel = "modelviewMatrix";
	constexpr auto fragColorLabel = "fragColor";

	struct Uniform {
		GLuint projectionMatrix;
		GLuint modelViewMatrix;
	};
	Uniform uniform;

	struct VertexAttribute
	{
		GLuint position;
		GLuint color;
		GLuint size;
	};
	VertexAttribute va;
}

void PointRenderer::link()
{
	uniform.projectionMatrix = shader->findUniformLocation(::projectionMatrixLabel);
	uniform.modelViewMatrix = shader->findUniformLocation(::modelViewMatrixLabel);

	va.position = shader->findAttribLocation(::positionLabel);
	va.color = shader->findAttribLocation(::colorLabel);
	va.size = shader->findAttribLocation(::sizeLabel);
}

void PointRenderer::render()
{
	shader->bind();

	shader->sendUniform(uniform.projectionMatrix, buffer.projectionMatrix);
	shader->sendUniform(uniform.modelViewMatrix, buffer.modelViewMatrix);

	shader->sendVertexAttribute3df(va.position, *buffer.position);
	shader->sendVertexAttribute4df(va.color, *buffer.color);
	shader->sendVertexAttribute1df(va.size, *buffer.size);

	shader->enableDepthTest();
	shader->enablePointSprite();

	shader->drawPoints(buffer.count);

	shader->bindOutput(::fragColorLabel);

	shader->disablePointSprite();
	shader->disableDepthTest();

	shader->unbind();

	assert(GL_NO_ERROR == glGetError());
}
