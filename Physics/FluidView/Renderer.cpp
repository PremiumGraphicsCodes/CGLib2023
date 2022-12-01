#include "Renderer.h"

#include "CGLib/Shader/ShaderBuilder.h"
#include "Crystal/Renderer/Renderer/PointShaderSource.h"

using namespace Crystal::Shader;
using namespace Crystal::Renderer;
using namespace Crystal::UI;

void Renderer::init()
{
	ShaderBuilder builder;
	builder.build(PointShaderSource::getVertexShaderSource(), PointShaderSource::getFragmentShaderSource());
	point.setShader(builder.getShader());
	point.link();

	/*
	builder.buildFromFile("../GLSL/Line.vs", "../GLSL/Line.fs");
	line.setShader(builder.getShader());
	line.link();

	builder.buildFromFile("../GLSL/Triangle.vs", "../GLSL/Triangle.fs");
	triangle.setShader(builder.getShader());
	triangle.link();
	*/

}

void Renderer::render(const Graphics::Camera& camera, const int width, const int height)
{
	assert(GL_NO_ERROR == glGetError());
	glViewport(0, 0, width, height);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto children = world->getRootScene()->getChildren();
	for (auto c : children) {
		for (auto p : c->getPresenters()) {
			p->render(camera);
		}
	}
	//presenter.render(camera);
	//wfPresenter->render(camera);
	assert(GL_NO_ERROR == glGetError());
}