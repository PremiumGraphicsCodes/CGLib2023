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

	struct UniformLoc {
		GLuint projectionMatrix;
		GLuint modelViewMatrix;
	};
	UniformLoc uniform;

	struct VertexAttributeLoc
	{
		GLuint position;
		GLuint color;
		GLuint size;
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

	Uniform projectionMatrix(uniform.projectionMatrix);
	Uniform modelviewMatrix(uniform.modelViewMatrix);

	projectionMatrix.send(buffer.projectionMatrix);
	modelviewMatrix.send(buffer.modelViewMatrix);

	VertexAttribute posAttr(va.position);
	VertexAttribute colAttr(va.color);
	VertexAttribute sizeAttr(va.size);

	posAttr.sendVertexAttribute3df(*buffer.position);
	colAttr.sendVertexAttribute4df(*buffer.color);
	sizeAttr.sendVertexAttribute1df(*buffer.size);

	shader->enable(GL_DEPTH_TEST);
	shader->enable(GL_POINT_SPRITE);
	shader->enable(GL_VERTEX_PROGRAM_POINT_SIZE);

	shader->drawPoints(buffer.count);

	shader->bindOutput(::fragColorLabel);

	shader->disable(GL_DEPTH_TEST);
	shader->disable(GL_POINT_SPRITE);
	shader->disable(GL_VERTEX_PROGRAM_POINT_SIZE);

	shader->unbind();

	assert(GL_NO_ERROR == glGetError());
}