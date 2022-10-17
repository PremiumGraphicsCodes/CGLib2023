#include "Renderer.h"

#include "CGLib/Shader/ShaderBuilder.h"

using namespace Crystal::UI;

void Renderer::onInit()
{
	Crystal::Shader::ShaderBuilder builder;
	builder.buildFromFile("../GLSL/Point.vs", "../GLSL/Point.fs");
	point.setShader(builder.getShader());
	point.link();

	builder.buildFromFile("../GLSL/Line.vs", "../GLSL/Line.fs");
	line.setShader(builder.getShader());
	line.link();

	builder.buildFromFile("../GLSL/Triangle.vs", "../GLSL/Triangle.fs");
	triangle.setShader(builder.getShader());
	triangle.link();

	builder.buildFromFile("../GLSL/ParticleDepth.glvs", "../GLSL/ParticleDepth.glfs");
	particleDepth.setShader(builder.getShader());
	particleDepth.link();

	builder.buildFromFile("../GLSL/SSThickness.glvs", "../GLSL/SSThickness.glfs");
	thickness.setShader(builder.getShader());
	thickness.link();
}
