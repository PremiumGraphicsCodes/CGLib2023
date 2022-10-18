#include "RendererBase.h"
#include "WorldBase.h"

#include "CGLib/Shader/ShaderBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

RendererBase::RendererBase(WorldBase* world) :
	world(world)
{}

void RendererBase::init()
{
	onInit();
}

void RendererBase::render(const int width, const int height)
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