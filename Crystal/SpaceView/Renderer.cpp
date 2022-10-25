#include "Renderer.h"
#include "CGLib/Shader/ShaderBuilder.h"

using namespace Crystal::Shader;
using namespace Crystal::UI;

void Renderer::init()
{
	ShaderBuilder builder;
	builder.buildFromFile("../GLSL/Point.vs", "../GLSL/Point.fs");
	point.setShader(builder.getShader());
	point.link();
}