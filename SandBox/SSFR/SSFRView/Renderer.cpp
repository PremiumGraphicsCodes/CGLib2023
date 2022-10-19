#include "Renderer.h"

#include "CGLib/Shader/ShaderBuilder.h"
#include "World.h"

using namespace Crystal::Graphics;
using namespace Crystal::Renderer;
using namespace Crystal::Shader;
using namespace Crystal::UI;

void Renderer::init()
{
	ShaderBuilder builder;
	builder.buildFromFile("../GLSL/ParticleDepth.glvs", "../GLSL/ParticleDepth.glfs");
	renderers.depth.setShader(builder.getShader());
	renderers.depth.link();

	builder.buildFromFile("../GLSL/SSThickness.glvs", "../GLSL/SSThickness.glfs");
	renderers.thickness.setShader(builder.getShader());
	renderers.thickness.link();

	builder.buildFromFile("../GLSL/SSNormal.glvs", "../GLSL/SSNormal.glfs");
	renderers.normal.setShader(builder.getShader());
	renderers.normal.link();
	/*
	builder.buildFromFile("../GLSL/SSReflection.glvs", "../GLSL/SSReflection.glfs");
	reflection.setShader(builder.getShader());
	reflection.link();

	builder.buildFromFile("../GLSL/SSFluid.glvs", "../GLSL/SSFluid.glfs");
	fluid.setShader(builder.getShader());
	fluid.link();
	*/

	builder.buildFromFile("../GLSL/BilateralFilter.glvs", "../GLSL/BilateralFilter.glfs");
	renderers.bilateralFilter.setShader(builder.getShader());
	renderers.bilateralFilter.link();

	builder.buildFromFile("../GLSL/SSAbsorption.glvs", "../GLSL/SSAbsorption.glfs");
	renderers.absorption.setShader(builder.getShader());
	renderers.absorption.link();

	builder.buildFromFile("../GLSL/Tex.vs", "../GLSL/Tex.fs");
	renderers.tex.setShader(builder.getShader());
	renderers.tex.link();

	std::vector<float> positions = { 0.0f, 0.0f, 0.0f };
	buffer.position.create();
	buffer.position.send(positions);

	std::vector<float> sizes = { 10.0f };
	buffer.pointSize.create();
	buffer.pointSize.send(sizes);

	std::vector<float> uvecs = { 1.0f, 0.0f, 0.0f };
	buffer.uvec.create();
	buffer.uvec.send(uvecs);

	std::vector<float> vvecs = { 0.0f, 1.0f, 0.0f };
	buffer.vvec.create();
	buffer.vvec.send(vvecs);

	std::vector<float> wvecs = { 0.0f, 0.0f, 1.0f };
	buffer.wvec.create();
	buffer.wvec.send(wvecs);

	buffer.pointCount = 1;

	this->fbo.create();
	this->textures.depthTexture.create();
	this->textures.depthTexture.send(Imageuc(512, 512));

	this->textures.filteredDepthTexture.create();
	this->textures.filteredDepthTexture.send(Imageuc(512, 512));

	this->textures.thicknessTexture.create();
	this->textures.thicknessTexture.send(Imageuc(512, 512));

	this->textures.normalTexture.create();
	this->textures.normalTexture.send(Imageuc(512, 512));

	this->textures.absorptionTexture.create();
	this->textures.absorptionTexture.send(Imageuc(512, 512));
}

void Renderer::render(const int width, const int height)
{
	assert(GL_NO_ERROR == glGetError());

	renderDepth(*world->getCamera());
	filterDepth();
	renderThickness(*world->getCamera());
	renderNormal(*world->getCamera());
	renderAbsorption();

	glViewport(0, 0, width, height);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderers.tex.buffer.tex = &this->textures.absorptionTexture; //&this->textures.filteredDepthTexture;
	renderers.tex.render();

	//presenter.render(camera);
	//wfPresenter->render(camera);
	assert(GL_NO_ERROR == glGetError());
}

void Renderer::renderDepth(const Camera& camera)
{
	this->fbo.bind();
	this->fbo.setTexture(this->textures.depthTexture);

	glViewport(0, 0, this->textures.depthTexture.getWidth(), this->textures.depthTexture.getHeight());
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ParticleDepthRenderer::Buffer pdBuffer;
	pdBuffer.modelViewMatrix = camera.getModelViewMatrix();
	pdBuffer.projectionMatrix = camera.getProjectionMatrix();
	pdBuffer.position = &this->buffer.position;
	pdBuffer.size = &this->buffer.pointSize;
	pdBuffer.count = this->buffer.pointCount;
	pdBuffer.uvec = &this->buffer.uvec;
	pdBuffer.vvec = &this->buffer.vvec;
	pdBuffer.wvec = &this->buffer.wvec;
	renderers.depth.buffer = pdBuffer;

	renderers.depth.render();

	this->fbo.unbind();
}

void Renderer::filterDepth()
{
	this->fbo.bind();
	this->fbo.setTexture(this->textures.filteredDepthTexture);

	glViewport(0, 0, textures.depthTexture.getWidth(), textures.depthTexture.getHeight());
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	BilateralFilterRenderer::Buffer buffer;
	buffer.texture = &this->textures.depthTexture;
	renderers.bilateralFilter.buffer = buffer;
	renderers.bilateralFilter.render();

	this->fbo.unbind();
}

void Renderer::renderThickness(const Graphics::Camera& camera)
{
	this->fbo.bind();
	this->fbo.setTexture(this->textures.thicknessTexture);

	glViewport(0, 0, textures.depthTexture.getWidth(), textures.depthTexture.getHeight());
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SSThicknessRenderer::Buffer buffer;
	buffer.projectionMatrix = camera.getProjectionMatrix();
	buffer.modelviewMatrix = camera.getModelViewMatrix();
	buffer.position = &this->buffer.position;
	buffer.pointSize = &this->buffer.pointSize;
	buffer.pointCount = this->buffer.pointCount;
	buffer.uvec = &this->buffer.uvec;
	buffer.vvec = &this->buffer.vvec;
	buffer.wvec = &this->buffer.wvec;
	renderers.thickness.buffer = buffer;

	renderers.thickness.render();

	this->fbo.unbind();
}

void Renderer::renderNormal(const Camera& camera)
{
	this->fbo.bind();
	this->fbo.setTexture(this->textures.normalTexture);

	glViewport(0, 0, textures.depthTexture.getWidth(), textures.depthTexture.getHeight());
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SSNormalRenderer::Buffer buffer;
	buffer.depthTexture = &this->textures.filteredDepthTexture;
	buffer.projectionMatrix = camera.getProjectionMatrix();
	renderers.normal.buffer = buffer;
	renderers.normal.render();

	this->fbo.unbind();
}

void Renderer::renderAbsorption()
{
	this->fbo.bind();
	this->fbo.setTexture(this->textures.absorptionTexture);

	glViewport(0, 0, textures.depthTexture.getWidth(), textures.depthTexture.getHeight());
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SSAbsorptionRenderer::Buffer buffer;
	buffer.volumeTexture = &this->textures.thicknessTexture;
	renderers.absorption.buffer = buffer;

	renderers.absorption.render();

	this->fbo.unbind();
}
