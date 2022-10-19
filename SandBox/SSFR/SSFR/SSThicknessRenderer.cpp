#include "SSThicknessRenderer.h"

#include "CGLib/Shader/Uniform.h"

using namespace Crystal::Shader;
using namespace Crystal::Renderer;

namespace {
	constexpr auto projectionMatrixLabel = "projectionMatrix";
	constexpr auto modelViewMatrixLabel = "modelviewMatrix";
	constexpr auto positionLabel = "position";
	constexpr auto pointSizeLabel = "pointSize";
	constexpr auto uvecLabel = "uvec";
	constexpr auto vvecLabel = "vvec";
	constexpr auto wvecLabel = "wvec";
	constexpr auto fragColorLabel = "fragColor";

	struct UniformLoc {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
	};
	UniformLoc uniformLoc;

	struct VertexAttrLoc {
		GLuint position;
		GLuint size;
		GLuint uvec;
		GLuint vvec;
		GLuint wvec;
	};
	VertexAttrLoc va;
}

void SSThicknessRenderer::link()
{
	::uniformLoc.projectionMatrix = shader->findUniformLocation(::projectionMatrixLabel);
	::uniformLoc.modelviewMatrix = shader->findUniformLocation(::modelViewMatrixLabel);

	::va.position = shader->findAttribLocation(::positionLabel);
	::va.size = shader->findAttribLocation(::pointSizeLabel);

	::va.uvec = shader->findAttribLocation(::uvecLabel);
	::va.vvec = shader->findAttribLocation(::vvecLabel);
	::va.wvec = shader->findAttribLocation(::wvecLabel);
}

void SSThicknessRenderer::render()
{
	shader->bind();

	Uniform projectionMatrix(uniformLoc.projectionMatrix);
	Uniform modelviewMatrix(uniformLoc.modelviewMatrix);

	projectionMatrix.send(buffer.projectionMatrix);
	modelviewMatrix.send(buffer.modelviewMatrix);

	VertexAttribute posAttr(va.position);
	VertexAttribute sizeAttr(va.size);
	VertexAttribute uvecAttr(va.uvec);
	VertexAttribute vvecAttr(va.vvec);
	VertexAttribute wvecAttr(va.wvec);

	posAttr.sendVertexAttribute3df(*buffer.position);
	sizeAttr.sendVertexAttribute1df(*buffer.pointSize);
	uvecAttr.sendVertexAttribute3df(*buffer.uvec);
	vvecAttr.sendVertexAttribute3df(*buffer.vvec);
	wvecAttr.sendVertexAttribute3df(*buffer.wvec);

	shader->enable(GL_DEPTH_TEST);
	shader->enable(GL_POINT_SPRITE);
	shader->enable(GL_VERTEX_PROGRAM_POINT_SIZE);

	shader->drawPoints(buffer.pointCount);

	shader->bindOutput(::fragColorLabel);

	shader->disable(GL_DEPTH_TEST);
	shader->disable(GL_POINT_SPRITE);
	shader->disable(GL_VERTEX_PROGRAM_POINT_SIZE);

	shader->unbind();

	assert(GL_NO_ERROR == glGetError());
}
