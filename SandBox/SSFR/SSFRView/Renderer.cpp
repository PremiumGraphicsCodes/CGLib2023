#include "Renderer.h"

#include "CGLib/Shader/ShaderBuilder.h"
#include "World.h"

using namespace Crystal::Renderer;
using namespace Crystal::Shader;
using namespace Crystal::UI;

void Renderer::init()
{
	ShaderBuilder builder;
	builder.buildFromFile("../GLSL/ParticleDepth.glvs", "../GLSL/ParticleDepth.glfs");
	renderers.depth.setShader(builder.getShader());
	renderers.depth.link();

	/*
	builder.buildFromFile("../GLSL/SSThickness.glvs", "../GLSL/SSThickness.glfs");
	thickness.setShader(builder.getShader());
	thickness.link();

	builder.buildFromFile("../GLSL/SSReflection.glvs", "../GLSL/SSReflection.glfs");
	reflection.setShader(builder.getShader());
	reflection.link();

	builder.buildFromFile("../GLSL/SSFluid.glvs", "../GLSL/SSFluid.glfs");
	fluid.setShader(builder.getShader());
	fluid.link();
	*/

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
}

void Renderer::render(const int width, const int height)
{
	assert(GL_NO_ERROR == glGetError());
	glViewport(0, 0, width, height);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderDepth(*world->getCamera());

	//presenter.render(camera);
	//wfPresenter->render(camera);
	assert(GL_NO_ERROR == glGetError());
}

void Crystal::UI::Renderer::renderDepth(const Graphics::Camera& camera)
{
	//this->fbo->bind();
	//this->fbo->setTexture(*this->textures.depthTexture);

	//glViewport(0, 0, textures.depthTexture->getWidth(), textures.depthTexture->getHeight());
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

	//this->fbo->unbind();
}
