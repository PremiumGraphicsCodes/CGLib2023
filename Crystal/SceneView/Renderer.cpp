#include "Renderer.h"

#include "CGLib/Shader/ShaderBuilder.h"
#include "Crystal/Renderer/PointShaderSource.h"

using namespace Crystal::UI;
using namespace Crystal::Renderer;

void Renderer::init()
{
	Crystal::Shader::ShaderBuilder builder;
	builder.build(PointShaderSource::getVertexShaderSource(), PointShaderSource::getFragmentShaderSource());
	point.setShader(builder.getShader());
	point.link();

	builder.buildFromFile("../GLSL/Line.vs", "../GLSL/Line.fs");
	line.setShader(builder.getShader());
	line.link();

	builder.buildFromFile("../GLSL/Triangle.vs", "../GLSL/Triangle.fs");
	triangle.setShader(builder.getShader());
	triangle.link();
}

void Renderer::render(const int width, const int height)
{
	assert(GL_NO_ERROR == glGetError());
	glViewport(0, 0, width, height);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto children = world->getRootScene()->getChildren();
	for (auto c : children) {
		c->getPresenter()->render(*world->getCamera());
	}
	//presenter.render(camera);
	//wfPresenter->render(camera);
	assert(GL_NO_ERROR == glGetError());
}