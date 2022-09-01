#include "TriangleRenderer.h"

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

void TriangleRenderer::link()
{
	vertexLoc.pos = shader->findAttribLocation(::positionLabel);
	vertexLoc.color = shader->findAttribLocation(::colorLabel);

	uniformLoc.projection = shader->findUniformLocation(::projectionMatrixLabel);
	uniformLoc.modelView = shader->findUniformLocation(::modelViewMatrixLabel);
}

void TriangleRenderer::render()
{
	shader->bind();

	shader->enable(GL_DEPTH_TEST);

	Uniform projection(uniformLoc.projection);
	Uniform modelView(uniformLoc.modelView);

	projection.send(buffer.projectionMatrix);
	modelView.send(buffer.modelViewMatrix);

	VertexAttribute position(vertexLoc.pos);
	VertexAttribute color(vertexLoc.color);

	position.sendVertexAttribute3df(*buffer.position);
	color.sendVertexAttribute4df(*buffer.color);

	shader->drawTriangles(buffer.indices);

	shader->bindOutput(::fragColorLabel);

	shader->disable(GL_DEPTH_TEST);

	shader->unbind();
}