#include "Renderer.h"

#include "CGLib/Shader/ShaderBuilder.h"
#include "Crystal/Renderer/PointShaderSource.h"
#include "Crystal/Renderer/LineShaderSource.h"
#include "Crystal/Renderer/TriangleShaderSource.h"

#include "Crystal/Scene/IPresenter.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Renderer;

Renderer::Renderer(World* world) :
	world(world)
{
	world->setRenderer(this);
}


void Renderer::init()
{
	Crystal::Shader::ShaderBuilder builder;
	builder.build(PointShaderSource::getVertexShaderSource(), PointShaderSource::getFragmentShaderSource());
	point.setShader(builder.getShader());
	point.link();

	builder.build(LineShaderSource::getVertexShaderSource(), LineShaderSource::getFragmentShaderSource());
	line.setShader(builder.getShader());
	line.link();

	builder.build(TriangleShaderSource::getVertexShaderSource(), TriangleShaderSource::getFragmentShaderSource());
	triangle.setShader(builder.getShader());
	triangle.link();
}

void Renderer::render(const Camera& camera, const int width, const int height)
{
	switch (target) {
	case Target::Main: {
		renderMain(camera, width, height);
		break;
	}
	case Target::Id: {
		renderId(camera, width, height);
		break;
	}
	default:
		assert(false);
	}
}

void Renderer::renderMain(const Camera& camera, const int width, const int height)
{
	assert(GL_NO_ERROR == glGetError());
	glViewport(0, 0, width, height);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	auto children = world->getRootScene()->getChildren();
	for (auto c : children) {
		c->getPresenter()->render(camera);
	}
	assert(GL_NO_ERROR == glGetError());
}

void Renderer::renderId(const Camera& camera, const int width, const int height)
{
	assert(GL_NO_ERROR == glGetError());
	glViewport(0, 0, width, height);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*
	const auto& presenters = world->getIdPresenters();
	for (auto& p : presenters) {
		p->render(camera);
	}
	*/
	assert(GL_NO_ERROR == glGetError());
}