#include "IRenderer.h"

#include "CGLib/Shader/ShaderBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

IRenderer::IRenderer() :
	camera(Vector3df(0, 0, 1), Vector3df(0, 0, 0), Vector3df(0, 1, 0), 0.1, 10.0)
{}

void IRenderer::init()
{
	Crystal::Shader::ShaderBuilder builder;
	builder.buildFromFile("../GLSL/Point.vs", "../GLSL/Point.fs");
	point.setShader(builder.getShader());
	point.link();

	builder.buildFromFile("../GLSL/Line.vs", "../GLSL/Line.fs");
	line.setShader(builder.getShader());
	line.link();

	onInit();
}
