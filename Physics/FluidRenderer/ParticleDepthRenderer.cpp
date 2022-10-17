#include "ParticleDepthRenderer.h"

using namespace Crystal::Shader;
using namespace Crystal::Renderer;

namespace {
	constexpr auto positionLabel = "position";
	constexpr auto colorLabel = "color";
	constexpr auto sizeLabel = "pointSize";
	constexpr auto projectionMatrixLabel = "projectionMatrix";
	constexpr auto modelViewMatrixLabel = "modelviewMatrix";
	constexpr auto fragColorLabel = "fragColor";

	struct UniformLoc {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
	};
	UniformLoc uniform;

	struct VertexAttr {
		GLuint position;
		GLuint color;
		GLuint size;
	};
	VertexAttr va;
}

void ParticleDepthRenderer::link()
{
	/*
	uniform.projectionMatrix = shader->findUniformLocation(::projectionMatrixLabel);
	uniform.modelviewMatrix = shader->findUniformLocation(::modelViewMatrixLabel);

	va.position = shader->findAttribLocation(::positionLabel);
	va.color = shader->findAttribLocation(::colorLabel);
	va.size = shader->findAttribLocation(::sizeLabel);
	*/
}

void ParticleDepthRenderer::render()
{
	/*
	shader->bind();

	Uniform projectionMatrix(uniform.projectionMatrix);
	Uniform modelviewMatrix(uniform.modelviewMatrix);

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
	*/
}