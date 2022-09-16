#include "RendererBase.h"
#include "IWorld.h"

#include "CGLib/Shader/ShaderBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

RendererBase::RendererBase(IWorld* world) :
	world(world),
	camera(Vector3df(0, 0, 1), Vector3df(0, 0, 0), Vector3df(0, 1, 0), 0.1, 10.0)
{}

void RendererBase::init()
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

void RendererBase::render(const int width, const int height)
{
	assert(GL_NO_ERROR == glGetError());
	glViewport(0, 0, width, height);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto children = world->rootScene.getChildren();
	for (auto c : children) {
		c->getPresenter()->render(*getCamera());
	}
	//presenter.render(camera);
	//wfPresenter->render(camera);
	assert(GL_NO_ERROR == glGetError());
}