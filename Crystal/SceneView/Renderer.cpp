#include "Renderer.h"

#include "CGLib/Shader/ShaderBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;


Renderer::Renderer(World* world) :
	world(world)
{}

void Renderer::onInit()
{
}

void Renderer::render(const int width, const int height)
{
	assert(GL_NO_ERROR == glGetError());
	glViewport(0, 0, width, height);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto children = world->rootScene.getChildren();
	for (auto c : children) {
		c->getPresenter()->render(*world->getCamera());
	}
	//presenter.render(camera);
	//wfPresenter->render(camera);
	assert(GL_NO_ERROR == glGetError());

}
