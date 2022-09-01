#include "TexShader.h"

#include "CGLib/Shader/ShaderBuilder.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Renderer;

void TexShader::build()
{
	ShaderBuilder sBuilder;

	sBuilder.buildFromFile("../GLSL/Tex.vs", "../GLSL/Tex.fs");

	renderer.setShader(sBuilder.getShader());
	renderer.link();

	tex.create();
	Imageuc image(2, 2);
	image.setColor(0, 0, ColorRGBAuc(0, 0, 0, 0));
	image.setColor(0, 1, ColorRGBAuc(255, 0, 0, 0));
	image.setColor(1, 0, ColorRGBAuc(0, 255, 0, 0));
	image.setColor(1, 1, ColorRGBAuc(0, 0, 255, 0));

	tex.send(image);
	tex.setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	tex.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	renderer.buffer.tex = &tex;
}

void TexShader::render(const Camera& camera, const int width, const int height)
{
	glViewport(0, 0, width, height);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderer.render();
}
