#include "ScreenRenderer.h"

#include "../Shader/ShaderBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::UI;

ScreenRenderer::ScreenRenderer() :
	camera(Vector3df(0, 0, 1), Vector3df(0, 0, 0), Vector3df(0, 1, 0), 0.1f, 10.0f)
{
	this->activeRenderer = &renderers.triangle;
}

void ScreenRenderer::setActiveRenderer(const RenderingType type)
{
	switch (type) {
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
