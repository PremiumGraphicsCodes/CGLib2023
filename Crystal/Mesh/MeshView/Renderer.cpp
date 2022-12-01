#include "Renderer.h"
#include "World.h"

#include "CGLib/Shader/ShaderBuilder.h"
#include "Crystal/Renderer/Renderer/PointShaderSource.h"
#include "Crystal/Renderer/Renderer/TriangleShaderSource.h"

using namespace Crystal::Shader;
using namespace Crystal::UI;
using namespace Crystal::Renderer;

Renderer::Renderer(World* world) :
	world(world)
{
	world->setRenderer(this);
}

void Renderer::init()
{
	ShaderBuilder builder;
	builder.build(PointShaderSource::getVertexShaderSource(), PointShaderSource::getFragmentShaderSource());
	point.setShader(builder.getShader());
	point.link();

	builder.build(TriangleShaderSource::getVertexShaderSource(), TriangleShaderSource::getFragmentShaderSource());
	triangle.setShader(builder.getShader());
	triangle.link();
}

void Renderer::render(const Graphics::Camera& camera, const int width, const int height)
{
	assert(GL_NO_ERROR == glGetError());
	glViewport(0, 0, width, height);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto presenters = world->getPresenters();
	for (auto p : presenters) {
		p->render(camera);
	}
	//presenter.render(camera);
	//wfPresenter->render(camera);
	assert(GL_NO_ERROR == glGetError());
}