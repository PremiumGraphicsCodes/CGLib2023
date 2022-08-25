#include "ScreenRenderer.h"

#include "../Shader/ShaderBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::UI;

ScreenRenderer::ScreenRenderer() :
	camera(Vector3df(0, 0, 1), Vector3df(0, 0, 0), Vector3df(0, 1, 0), 0.1f, 10.0f)
{
	this->activeRenderer = &renderers.pointRenderer;
}

void ScreenRenderer::setActiveRenderer(const RenderingType type)
{
	switch (type) {
	case RenderingType::Point :
		this->activeRenderer = &renderers.pointRenderer;
		break;
	case RenderingType::Line :
		this->activeRenderer = &renderers.lineRenderer;
		break;
	case RenderingType::Triangle :
		this->activeRenderer = &renderers.triangleRenderer;
		break;
	case RenderingType::Tex :
		this->activeRenderer = &renderers.texRenderer;
		break;
	default:
		assert(false);
	}
}

void ScreenRenderer::build()
{
	ShaderBuilder sBuilder;
	sBuilder.buildFromFile("./Point.vs", "./Point.fs");

	renderers.pointRenderer.setShader(sBuilder.getShader());
	renderers.pointRenderer.link();

	sBuilder.buildFromFile("./Line.vs", "./Line.fs");
	renderers.lineRenderer.setShader(sBuilder.getShader());
	renderers.lineRenderer.link();

	sBuilder.buildFromFile("./Triangle.vs", "./Triangle.fs");
	renderers.triangleRenderer.setShader(sBuilder.getShader());
	renderers.triangleRenderer.link();

	sBuilder.buildFromFile("./Tex.vs", "./Tex.fs");

	renderers.texRenderer.setShader(sBuilder.getShader());
	renderers.texRenderer.link();

	tex.create();
	Imageuc image(2, 2);
	image.setColor(0, 0, ColorRGBAuc(0, 0, 0, 0));
	image.setColor(0, 1, ColorRGBAuc(255, 0, 0, 0));
	image.setColor(1, 0, ColorRGBAuc(0, 255, 0, 0));
	image.setColor(1, 1, ColorRGBAuc(0, 0, 255, 0));

	tex.send(image);
	tex.setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	tex.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	renderers.texRenderer.buffer.tex = &tex;

	buffers.positionVBO.create();
	buffers.colorVBO.create();
	buffers.sizeVBO.create();

	std::vector<float> positions{ 0,0,0, 1,0,0, 0,1,0 };
	std::vector<float> colors{ 1,1,1,1, 1,0,0,0, 0,1,0,0 };
	std::vector<float> size{ 100 };
	buffers.positionVBO.send(positions);
	buffers.colorVBO.send(colors);
	buffers.sizeVBO.send(size);

	renderers.pointRenderer.buffer.position = &buffers.positionVBO;
	renderers.pointRenderer.buffer.color = &buffers.colorVBO;
	renderers.pointRenderer.buffer.size = &buffers.sizeVBO;
	renderers.pointRenderer.buffer.modelViewMatrix = camera.getModelViewMatrix();
	renderers.pointRenderer.buffer.projectionMatrix = camera.getProjectionMatrix();
	renderers.pointRenderer.buffer.count = 1;

	renderers.lineRenderer.buffer.position = &buffers.positionVBO;
	renderers.lineRenderer.buffer.color = &buffers.colorVBO;
	renderers.lineRenderer.buffer.modelViewMatrix = camera.getModelViewMatrix();
	renderers.lineRenderer.buffer.projectionMatrix = camera.getProjectionMatrix();
	renderers.lineRenderer.buffer.indices = { 0, 1 };
	renderers.lineRenderer.buffer.lineWidth = 10.0f;

	renderers.triangleRenderer.buffer.position = &buffers.positionVBO;
	renderers.triangleRenderer.buffer.color = &buffers.colorVBO;
	renderers.triangleRenderer.buffer.modelViewMatrix = camera.getModelViewMatrix();
	renderers.triangleRenderer.buffer.projectionMatrix = camera.getProjectionMatrix();
	renderers.triangleRenderer.buffer.indices = { 0, 1, 2 };
}

void ScreenRenderer::render(const int width, const int height)
{
	glViewport(0, 0, width, height);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	activeRenderer->render();
}
