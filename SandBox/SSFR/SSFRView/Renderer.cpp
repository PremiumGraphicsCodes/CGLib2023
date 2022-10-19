#include "Renderer.h"

#include "CGLib/Shader/ShaderBuilder.h"
#include "CGLib/Graphics/ImageFileReader.h"
#include "World.h"

using namespace Crystal::Graphics;
using namespace Crystal::Renderer;
using namespace Crystal::Shader;
using namespace Crystal::UI;

namespace {
	bool readCubeMap(CubeMapTextureObject& cubeMap)
	{
		std::array<Imageuc, 6> images;

		ImageFileReader reader;
		if (!reader.read("../../../ThirdParty/forest-skyboxes/Brudslojan/posx.jpg")) {
			return false;
		}
		images[0] = reader.toImage();
		if (!reader.read("../../../ThirdParty/forest-skyboxes/Brudslojan/negx.jpg")) {
			return false;
		}
		images[1] = reader.toImage();
		if (!reader.read("../../../ThirdParty/forest-skyboxes/Brudslojan/posy.jpg")) {
			return false;
		}
		images[2] = reader.toImage();
		if (!reader.read("../../../ThirdParty/forest-skyboxes/Brudslojan/negy.jpg")) {
			return false;
		}
		images[3] = reader.toImage();
		if (!reader.read("../../../ThirdParty/forest-skyboxes/Brudslojan/posz.jpg")) {
			return false;
		}
		images[4] = reader.toImage();
		if (!reader.read("../../../ThirdParty/forest-skyboxes/Brudslojan/negz.jpg")) {
			return false;
		}
		images[5] = reader.toImage();
		cubeMap.create();
		cubeMap.send(images);
		return true;
	}
}

void Renderer::init()
{
	ShaderBuilder builder;

	builder.buildFromFile("../GLSL/SkyBox.vs", "../GLSL/SkyBox.fs");
	renderers.skyBox.setShader(builder.getShader());
	renderers.skyBox.link();

	builder.buildFromFile("../GLSL/ParticleDepth.vs", "../GLSL/ParticleDepth.fs");
	renderers.depth.setShader(builder.getShader());
	renderers.depth.link();

	builder.buildFromFile("../GLSL/SSThickness.vs", "../GLSL/SSThickness.fs");
	renderers.thickness.setShader(builder.getShader());
	renderers.thickness.link();

	builder.buildFromFile("../GLSL/SSNormal.vs", "../GLSL/SSNormal.fs");
	renderers.normal.setShader(builder.getShader());
	renderers.normal.link();

	builder.buildFromFile("../GLSL/SSReflection.vs", "../GLSL/SSReflection.fs");
	renderers.reflection.setShader(builder.getShader());
	renderers.reflection.link();

	builder.buildFromFile("../GLSL/SSRefraction.vs", "../GLSL/SSRefraction.fs");
	renderers.refraction.setShader(builder.getShader());
	renderers.refraction.link();

	builder.buildFromFile("../GLSL/BilateralFilter.vs", "../GLSL/BilateralFilter.fs");
	renderers.bilateralFilter.setShader(builder.getShader());
	renderers.bilateralFilter.link();

	builder.buildFromFile("../GLSL/SSAbsorption.vs", "../GLSL/SSAbsorption.fs");
	renderers.absorption.setShader(builder.getShader());
	renderers.absorption.link();

	builder.buildFromFile("../GLSL/SSDeffered.vs", "../GLSL/SSDeffered.fs");
	renderers.deffered.setShader(builder.getShader());
	renderers.deffered.link();

	builder.buildFromFile("../GLSL/SSComposite.vs", "../GLSL/SSComposite.fs");
	renderers.composite.setShader(builder.getShader());
	renderers.composite.link();

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

	this->textures.background.create();
	this->textures.background.send(Imageuc(512, 512));

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

	this->textures.reflectedTexture.create();
	this->textures.reflectedTexture.send(Imageuc(512, 512));

	this->textures.refractedTexture.create();
	this->textures.refractedTexture.send(Imageuc(512, 512));

	this->textures.shadedTexture.create();
	this->textures.shadedTexture.send(Imageuc(512, 512));

	this->textures.composite.create();
	this->textures.composite.send(Imageuc(512, 512));

	readCubeMap(this->textures.cubeMap);
}

void Renderer::render(const int width, const int height)
{
	assert(GL_NO_ERROR == glGetError());

	const auto camera = *world->getCamera();

	renderBackGround(camera);
	renderDepth(camera);
	filterDepth();
	renderThickness(camera);
	renderNormal(camera);
	renderAbsorption();
	renderReflection(camera);
	renderRefraction(camera);

	glViewport(0, 0, width, height);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderers.tex.buffer.tex = &this->textures.refractedTexture; //&this->textures.filteredDepthTexture;
	renderers.tex.render();

	//presenter.render(camera);
	//wfPresenter->render(camera);
	assert(GL_NO_ERROR == glGetError());
}

void Renderer::renderBackGround(const Camera& camera)
{
	this->fbo.bind();
	this->fbo.setTexture(this->textures.background);
	//this->texture->bind(0);

	glViewport(0, 0, textures.depthTexture.getWidth(), textures.depthTexture.getHeight());
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SkyBoxRenderer::Buffer buffer;
	buffer.cubeMapTexture = &this->textures.cubeMap;
	buffer.modelViewMatrix = glm::mat4(glm::mat3(camera.getModelViewMatrix()));//camera.getModelViewMatrix();
	buffer.projectionMatrix = camera.getProjectionMatrix();

	renderers.skyBox.buffer = buffer;
	renderers.skyBox.render();

	this->fbo.unbind();
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

void Renderer::renderReflection(const Graphics::Camera& camera)
{
	this->fbo.bind();
	this->fbo.setTexture(this->textures.reflectedTexture);

	glViewport(0, 0, textures.depthTexture.getWidth(), textures.depthTexture.getHeight());
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SSReflectionRenderer::Buffer buffer;
	buffer.cubeMapTexture = &this->textures.cubeMap;
	buffer.depthTexture = &this->textures.filteredDepthTexture;
	buffer.normalTexture = &this->textures.normalTexture;
	buffer.eyePosition = camera.getEye();
	buffer.projectionMatrix = camera.getProjectionMatrix();

	renderers.reflection.buffer = buffer;
	renderers.reflection.render();

	this->fbo.unbind();
}

void Renderer::renderRefraction(const Graphics::Camera& camera)
{
	this->fbo.bind();
	this->fbo.setTexture(this->textures.refractedTexture);

	glViewport(0, 0, textures.depthTexture.getWidth(), textures.depthTexture.getHeight());
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SSRefractionRenderer::Buffer buffer;
	buffer.cubeMapTexture = &this->textures.cubeMap;
	buffer.depthTexture = &this->textures.filteredDepthTexture;
	buffer.normalTexture = &this->textures.normalTexture;
	buffer.eyePosition = camera.getEye();
	buffer.projectionMatrix = camera.getProjectionMatrix();

	renderers.refraction.buffer = buffer;
	renderers.refraction.render();

	this->fbo.unbind();

}
