#include "Renderer.h"

#include "CGLib/Shader/ShaderBuilder.h"

using namespace Crystal::Shader;
using namespace Crystal::UI;

void Renderer::init()
{
	ShaderBuilder builder;
	builder.buildFromFile("../GLSL/ParticleDepth.glvs", "../GLSL/ParticleDepth.glfs");
	particleDepth.setShader(builder.getShader());
	particleDepth.link();

	builder.buildFromFile("../GLSL/SSThickness.glvs", "../GLSL/SSThickness.glfs");
	thickness.setShader(builder.getShader());
	thickness.link();

	builder.buildFromFile("../GLSL/SSReflection.glvs", "../GLSL/SSReflection.glfs");
	reflection.setShader(builder.getShader());
	reflection.link();

	builder.buildFromFile("../GLSL/SSFluid.glvs", "../GLSL/SSFluid.glfs");
	fluid.setShader(builder.getShader());
	fluid.link();
}

void Renderer::render(const int width, const int height)
{
	/*
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
	*/
}