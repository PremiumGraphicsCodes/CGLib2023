#include "Renderer.h"

#include "CGLib/Shader/ShaderBuilder.h"
#include "Crystal/Renderer/PointShaderSource.h"
#include "Crystal/Renderer/LineShaderSource.h"
#include "Crystal/Renderer/TriangleShaderSource.h"
#include "Crystal/Renderer/TexShaderSource.h"

#include "Crystal/Scene/Scene/IPresenter.h"

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
	renderers.point.setShader(builder.getShader());
	renderers.point.link();

	builder.build(LineShaderSource::getVertexShaderSource(), LineShaderSource::getFragmentShaderSource());
	renderers.line.setShader(builder.getShader());
	renderers.line.link();

	builder.build(TriangleShaderSource::getVertexShaderSource(), TriangleShaderSource::getFragmentShaderSource());
	renderers.triangle.setShader(builder.getShader());
	renderers.triangle.link();

	builder.build(TexShaderSource::getVertexShaderSource(), TexShaderSource::getFragmentShaderSource());
	renderers.tex.setShader(builder.getShader());
	renderers.tex.link();

	this->fbo.create();

	this->textures.main.create();
	this->textures.main.send(Imageuc(512, 512));
	this->textures.id.create();
	this->textures.id.send(Imageuc(512, 512));
}

void Renderer::render(const Camera& camera, const int width, const int height)
{
	renderMain(camera);
	renderId(camera);

	glViewport(0, 0, width, height);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (target) {
	case Target::Main: {
		this->renderers.tex.buffer.tex = &this->textures.main;
		break;
	}
	case Target::Id: {
		this->renderers.tex.buffer.tex = &this->textures.id;
		break;
	}
	default:
		assert(false);
	}
	this->renderers.tex.render();
}

void Renderer::renderMain(const Camera& camera)
{
	this->fbo.bind();
	this->fbo.setTexture(this->textures.main);

	assert(GL_NO_ERROR == glGetError());
	glViewport(0, 0, this->textures.main.getWidth(), this->textures.main.getHeight());
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	const auto& presenters = world->getPresenters();
	for (auto& p : presenters) {
		p->render(camera);
	}
	assert(GL_NO_ERROR == glGetError());

	this->fbo.unbind();
}

void Renderer::renderId(const Camera& camera)
{
	this->fbo.bind();
	this->fbo.setTexture(this->textures.id);

	assert(GL_NO_ERROR == glGetError());
	glViewport(0, 0, this->textures.id.getWidth(), this->textures.id.getHeight());
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	const auto& presenters = world->getIdPresenters();
	for (auto& p : presenters) {
		p->render(camera);
	}
	assert(GL_NO_ERROR == glGetError());

	this->fbo.unbind();
}