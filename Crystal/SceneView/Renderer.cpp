#include "Renderer.h"

#include "CGLib/Shader/ShaderBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

Renderer::Renderer(World* world) :
	world(world),
	camera(Vector3df(0, 0, 1), Vector3df(0, 0, 0), Vector3df(0, 1, 0), 0.1, 10.0)
{}

void Renderer::init()
{
	Crystal::Shader::ShaderBuilder builder;
	builder.buildFromFile("../GLSL/Point.vs", "../GLSL/Point.fs");
	point.setShader(builder.getShader());
	point.link();

	builder.buildFromFile("../GLSL/Line.vs", "../GLSL/Line.fs");
	line.setShader(builder.getShader());
	line.link();
}

void Renderer::addWireFrame()
{
	wfScene.add(new Vertex(Vector3df(0, 0, 0)));
	wfScene.add(new Vertex(Vector3df(1, 0, 0)));
	wfScene.addIndex(0);
	wfScene.addIndex(1);


	auto wfPresenter = std::make_unique<Crystal::Scene::WireFramePresenter>(&wfScene, &line);
	wfPresenter->build();
	wfPresenter->send();
	wfScene.setPresenter(std::move(wfPresenter));

	rootScene.addScene(&wfScene);
}

void Renderer::add(IScene* scene)
{
	rootScene.addScene(scene);
}

void Renderer::render(const int width, const int height)
{
	assert(GL_NO_ERROR == glGetError());
	glViewport(0, 0, width, height);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto children = rootScene.getChildren();
	for (auto c : children) {
		c->getPresenter()->render(camera);
	}
	//presenter.render(camera);
	//wfPresenter->render(camera);
	assert(GL_NO_ERROR == glGetError());

}
