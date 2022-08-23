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

void Renderer::build()
{
	ShaderBuilder builder;
	builder.build(vsSource, fsSource);
	this->shader = builder.getShader();
}
