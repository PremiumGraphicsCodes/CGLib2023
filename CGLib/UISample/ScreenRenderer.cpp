#include "ScreenRenderer.h"

#include "../Shader/ShaderBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::UI;

ScreenRenderer::ScreenRenderer() :
	camera(Vector3df(0, 0, 1), Vector3df(0, 0, 0), Vector3df(0, 1, 0), 0.1, 10.0)
{
	this->activeRenderer = &renderer;
}

void ScreenRenderer::setActiveRenderer(const RenderingType type)
{
	switch (type) {
	case RenderingType::Point :
		this->activeRenderer = &renderer;
		break;
	case RenderingType::Tex :
		this->activeRenderer = &texRenderer;
		break;
	default:
		assert(false);
	}
}


void ScreenRenderer::build()
{
	ShaderBuilder sBuilder;
	sBuilder.buildFromFile("./Point.vs", "./Point.fs");

	renderer.setShader(sBuilder.getShader());
	renderer.link();

	sBuilder.buildFromFile("./Tex.vs", "./Tex.fs");

	texRenderer.setShader(sBuilder.getShader());
	texRenderer.link();

	tex.create();
	Imageuc image(2, 2);
	image.setColor(0, 0, ColorRGBAuc(0, 0, 0, 0));
	image.setColor(0, 1, ColorRGBAuc(255, 0, 0, 0));
	image.setColor(1, 0, ColorRGBAuc(0, 255, 0, 0));
	image.setColor(1, 1, ColorRGBAuc(0, 0, 255, 0));

	tex.send(image);
	tex.setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	tex.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	texRenderer.buffer.tex = &tex;

	positionVBO.create();
	colorVBO.create();
	sizeVBO.create();

	std::vector<float> positions{ 0,0,0 };
	std::vector<float> colors{ 1,1,1,1 };
	std::vector<float> size{ 100 };
	positionVBO.send(positions);
	colorVBO.send(colors);
	sizeVBO.send(size);

	renderer.buffer.position = &positionVBO;
	renderer.buffer.color = &colorVBO;
	renderer.buffer.size = &sizeVBO;
	renderer.buffer.modelViewMatrix = camera.getModelViewMatrix();
	renderer.buffer.projectionMatrix = camera.getProjectionMatrix();
	renderer.buffer.count = 1;
}

void ScreenRenderer::render(const int width, const int height)
{
	glViewport(0, 0, width, height);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	activeRenderer->render();
}
