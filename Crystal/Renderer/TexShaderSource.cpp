#include "TexShaderSource.h"

using namespace Crystal::Renderer;

std::string TexShaderSource::getVertexShaderSource()
{
	const auto str = R"(
#version 150
in vec2 position;
out vec2 texCoord;
void main(void) {
	texCoord = (position + vec2(1.0,1.0))/2.0;
	gl_Position = vec4(position, 0.0, 1.0);
}
		)";
	return str;
}

std::string TexShaderSource::getFragmentShaderSource()
{
	const auto str = R"(
#version 150
uniform sampler2D texture;
in vec2 texCoord;
out vec4 fragColor;
void main(void) {
	fragColor = texture2D(texture, texCoord);
//	fragColor.r = 1.0;
}
)";
	return str;
}
