#include "SkyBoxShaderSource.h"

using namespace Crystal::Renderer;

std::string SkyBoxShaderSource::getVertexShaderSource()
{
	const auto str = R"(
#version 150
in vec3 position;
out vec3 vTexCoord;
uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;
void main(void) {
	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);
	vTexCoord = position;
}
		)";
	return str;
}

std::string SkyBoxShaderSource::getFragmentShaderSource()
{
	const auto str = R"(
#version 150
in vec3 vTexCoord;
out vec4 fragColor;
uniform samplerCube cubeMapTex;
void main(void) {
	fragColor = texture(cubeMapTex, vTexCoord);
	//fragColor.rgb = vec3(1,1,1);
}
)";
	return str;
}
