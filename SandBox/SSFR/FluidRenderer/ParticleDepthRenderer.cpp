#include "ParticleDepthRenderer.h"

using namespace Crystal::Shader;
using namespace Crystal::Renderer;

namespace {
	constexpr auto positionLabel = "position";
	constexpr auto sizeLabel = "pointSize";
	constexpr auto uvecLabel = "uvec";
	constexpr auto vvecLabel = "vvec";
	constexpr auto wvecLabel = "wvec";
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
		GLuint size;
		GLuint uvec;
		GLuint vvec;
		GLuint wvec;
	};
	VertexAttr va;
}

void ParticleDepthRenderer::link()
{
	uniform.projectionMatrix = shader->findUniformLocation(::projectionMatrixLabel);
	uniform.modelviewMatrix = shader->findUniformLocation(::modelViewMatrixLabel);

	va.position = shader->findAttribLocation(::positionLabel);
	va.size = shader->findAttribLocation(::sizeLabel);
	va.uvec = shader->findAttribLocation(::uvecLabel);
	va.vvec = shader->findAttribLocation(::vvecLabel);
	va.wvec = shader->findAttribLocation(::wvecLabel);
}

void ParticleDepthRenderer::render()
{
	shader->bind();

	Uniform projectionMatrix(uniform.projectionMatrix);
	Uniform modelviewMatrix(uniform.modelviewMatrix);

	projectionMatrix.send(buffer.projectionMatrix);
	modelviewMatrix.send(buffer.modelViewMatrix);

	VertexAttribute posAttr(va.position);
	VertexAttribute sizeAttr(va.size);
	VertexAttribute uvecAttr(va.uvec);
	VertexAttribute vvecAttr(va.vvec);
	VertexAttribute wvecAttr(va.wvec);

	posAttr.sendVertexAttribute3df(*buffer.position);
	sizeAttr.sendVertexAttribute1df(*buffer.size);
	uvecAttr.sendVertexAttribute3df(*buffer.uvec);
	vvecAttr.sendVertexAttribute3df(*buffer.vvec);
	wvecAttr.sendVertexAttribute3df(*buffer.wvec);

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