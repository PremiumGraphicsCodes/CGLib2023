#include "PointRenderer.h"

#include "../Shader/ShaderBuilder.h"

#include "../Shader/VertexAttribute.h"

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

	struct VertexAttributeLoc
	{
		VertexAttribute position;
		VertexAttribute color;
		VertexAttribute size;
	};
	VertexAttributeLoc va;
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

	va.position.sendVertexAttribute3df(*buffer.position);
	va.color.sendVertexAttribute4df(*buffer.color);
	va.size.sendVertexAttribute1df(*buffer.size);

	va.position.enableVertexAttribute();
	va.color.enableVertexAttribute();
	va.size.enableVertexAttribute();

	shader->enableDepthTest();
	shader->enablePointSprite();

	shader->drawPoints(buffer.count);

	shader->bindOutput(::fragColorLabel);

	shader->disablePointSprite();
	shader->disableDepthTest();

	va.position.disableVertexAttribute();
	va.color.disableVertexAttribute();
	va.size.disableVertexAttribute();

	shader->unbind();

	assert(GL_NO_ERROR == glGetError());
}
