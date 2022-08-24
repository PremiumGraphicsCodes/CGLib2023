#include "Renderer.h"

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

	struct Location{
		GLuint projectionMatrix;
		GLuint modelViewMatrix;
	};
	Location location;
}


void Renderer::build()
{
	ShaderBuilder builder;
	builder.build(vsSource, fsSource);
	this->shader = builder.getShader();

	location.projectionMatrix = shader->findUniformLocation(::projectionMatrixLabel);
	location.modelViewMatrix = shader->findUniformLocation(::modelViewMatrixLabel);

	shader->findAttribLocation(::positionLabel);
	shader->findAttribLocation(::colorLabel);
	shader->findAttribLocation(::sizeLabel);
}

void Renderer::render()
{
	shader->bind();


	shader->sendUniform(location.projectionMatrix, buffer.projectionMatrix);
	shader->sendUniform(location.modelViewMatrix, buffer.modelViewMatrix);


	//buffer.position->bind();

	shader->sendVertexAttribute3df(::positionLabel, *buffer.position);
	shader->sendVertexAttribute4df(::colorLabel, *buffer.color);
	shader->sendVertexAttribute1df(::sizeLabel, *buffer.size);

	assert(GL_NO_ERROR == glGetError());

	shader->enableDepthTest();
	shader->enablePointSprite();

	shader->drawPoints(buffer.count);

	assert(GL_NO_ERROR == glGetError());


	shader->bindOutput(::fragColorLabel);

	shader->disablePointSprite();
	shader->disableDepthTest();

	shader->unbind();

	assert(GL_NO_ERROR == glGetError());
}
