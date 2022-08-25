#include "ScreenRenderer.h"

#include "../Shader/ShaderBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::UI;

ScreenRenderer::ScreenRenderer() :
	camera(Vector3df(0, 0, 1), Vector3df(0, 0, 0), Vector3df(0, 1, 0), 0.1f, 10.0f)
{
	this->activeRenderer = &renderers.point;
}

void ScreenRenderer::setActiveRenderer(const RenderingType type)
{
	switch (type) {
	case RenderingType::Point :
		this->activeRenderer = &renderers.point;
		break;
	case RenderingType::Line :
		this->activeRenderer = &renderers.line;
		break;
	case RenderingType::Triangle :
		this->activeRenderer = &renderers.triangle;
		break;
	case RenderingType::Tex :
		this->activeRenderer = &renderers.tex;
		break;
	default:
		assert(false);
	}
}

void ScreenRenderer::build()
{
	ShaderBuilder sBuilder;
	sBuilder.buildFromFile("./Point.vs", "./Point.fs");

	renderers.point.setShader(sBuilder.getShader());
	renderers.point.link();

	sBuilder.buildFromFile("./Line.vs", "./Line.fs");
	renderers.line.setShader(sBuilder.getShader());
	renderers.line.link();

	sBuilder.buildFromFile("./Triangle.vs", "./Triangle.fs");
	renderers.triangle.setShader(sBuilder.getShader());
	renderers.triangle.link();

	sBuilder.buildFromFile("./Tex.vs", "./Tex.fs");

	renderers.tex.setShader(sBuilder.getShader());
	renderers.tex.link();

	tex.create();
	Imageuc image(2, 2);
	image.setColor(0, 0, ColorRGBAuc(0, 0, 0, 0));
	image.setColor(0, 1, ColorRGBAuc(255, 0, 0, 0));
	image.setColor(1, 0, ColorRGBAuc(0, 255, 0, 0));
	image.setColor(1, 1, ColorRGBAuc(0, 0, 255, 0));

	tex.send(image);
	tex.setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	tex.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	renderers.tex.buffer.tex = &tex;

	buffers.positionVBO.create();
	buffers.colorVBO.create();
	buffers.sizeVBO.create();

	std::vector<float> positions{ 0,0,0, 1,0,0, 0,1,0 };
	std::vector<float> colors{ 1,1,1,1, 1,0,0,0, 0,1,0,0 };
	std::vector<float> size{ 100 };
	buffers.positionVBO.send(positions);
	buffers.colorVBO.send(colors);
	buffers.sizeVBO.send(size);

	renderers.point.buffer.position = &buffers.positionVBO;
	renderers.point.buffer.color = &buffers.colorVBO;
	renderers.point.buffer.size = &buffers.sizeVBO;
	renderers.point.buffer.modelViewMatrix = camera.getModelViewMatrix();
	renderers.point.buffer.projectionMatrix = camera.getProjectionMatrix();
	renderers.point.buffer.count = 1;

	renderers.line.buffer.position = &buffers.positionVBO;
	renderers.line.buffer.color = &buffers.colorVBO;
	renderers.line.buffer.modelViewMatrix = camera.getModelViewMatrix();
	renderers.line.buffer.projectionMatrix = camera.getProjectionMatrix();
	renderers.line.buffer.indices = { 0, 1 };
	renderers.line.buffer.lineWidth = 10.0f;

	renderers.triangle.buffer.position = &buffers.positionVBO;
	renderers.triangle.buffer.color = &buffers.colorVBO;
	renderers.triangle.buffer.modelViewMatrix = camera.getModelViewMatrix();
	renderers.triangle.buffer.projectionMatrix = camera.getProjectionMatrix();
	renderers.triangle.buffer.indices = { 0, 1, 2 };
}

void ScreenRenderer::render(const int width, const int height)
{
	glViewport(0, 0, width, height);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	activeRenderer->render();
}
