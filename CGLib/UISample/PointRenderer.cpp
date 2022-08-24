#include "PointRenderer.h"

#include "../Shader/ShaderBuilder.h"

using namespace Crystal::Shader;
using namespace Crystal::UI;

namespace {
	const std::string vsSource = R"(
#version 150
in vec3 position;
in float pointSize;
in vec4 color;
out vec4 vColor;
uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;
void main(void) {
	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);
	gl_PointSize = pointSize / gl_Position.w;
	vColor = color;
}
)";

	const std::string fsSource = R"(
#version 150
in vec4 vColor;
out vec4 fragColor;
void main(void) {
	vec2 coord = gl_PointCoord * 2.0 - 1.0;
	float distSquared = 1.0 - dot(coord, coord);
	if (distSquared < 0.0) {
		discard;
	}
	fragColor.rgba = vColor;
	//fragColor.a = sqrt(distSquared) * vColor.a;
	//fragColor.a = 0.1;//sqrt(distSquared);
}
)";
}

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

void PointRenderer::build()
{
	ShaderBuilder builder;
	builder.build(vsSource, fsSource);
	this->shader = builder.getShader();

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
