#include "LineRenderer.h"

#include "CGLib/Shader/Uniform.h"

using namespace Crystal::Shader;
using namespace Crystal::Renderer;

namespace {
	constexpr const char* positionLabel = "position";
	constexpr const char* colorLabel = "color";
	constexpr const char* projectionMatrixLabel = "projectionMatrix";
	constexpr const char* modelViewMatrixLabel = "modelviewMatrix";
	constexpr const char* fragColorLabel = "fragColor";

	struct VertexLoc
	{
		GLuint pos;
		GLuint color;
	};
	VertexLoc vertexLoc;

	struct UniformLoc
	{
		GLuint projection;
		GLuint modelView;
	};
	UniformLoc uniformLoc;
}

void LineRenderer::link()
{
	vertexLoc.pos = shader->findAttribLocation(::positionLabel);
	vertexLoc.color = shader->findAttribLocation(::colorLabel);

	uniformLoc.projection = shader->findUniformLocation(::projectionMatrixLabel);
	uniformLoc.modelView = shader->findUniformLocation(::modelViewMatrixLabel);
}

void LineRenderer::render()
{
	shader->bind();

	assert(GL_NO_ERROR == glGetError());


	shader->enable(GL_DEPTH_TEST);

	Uniform projection(uniformLoc.projection);
	Uniform modelView(uniformLoc.modelView);

	projection.send(buffer.projectionMatrix);
	modelView.send(buffer.modelViewMatrix);

	VertexAttribute position(vertexLoc.pos);
	VertexAttribute color(vertexLoc.color);

	position.sendVertexAttribute3df(*buffer.position);
	color.sendVertexAttribute4df(*buffer.color);

	shader->setLineWidth(buffer.lineWidth);

	shader->drawLines(buffer.indices);

	shader->bindOutput(::fragColorLabel);

	shader->setLineWidth(1);

	shader->disable(GL_DEPTH_TEST);

	assert(GL_NO_ERROR == glGetError());


	shader->unbind();
}