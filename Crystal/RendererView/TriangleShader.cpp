#include "TriangleShader.h"

#include "CGLib/Shader/ShaderBuilder.h"
#include "CGLib/Shader/VertexBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Renderer;

void TriangleShader::build()
{
	ShaderBuilder builder;
	builder.buildFromFile("../GLSL/Triangle.vs", "../GLSL/Triangle.fs");
	renderer.setShader(builder.getShader());
	renderer.link();

	VertexBuffer<float> vb;
	vb.add(Vector3df(0.0, 0.0, 0.0));
	vb.add(Vector3df(0.1, 0.0, 0.0));
	vb.add(Vector3df(0.1, 0.1, 0.0));

	VertexBuffer<float> colorBuffer;
	colorBuffer.add(ColorRGBAf(1, 0, 0, 1));
	colorBuffer.add(ColorRGBAf(0, 1, 0, 1));
	colorBuffer.add(ColorRGBAf(1, 1, 0, 1));

	positions.create();
	colors.create();

	positions.send(vb);
	colors.send(colorBuffer.getData());

	renderer.buffer.position = &positions;
	renderer.buffer.color = &colors;

	renderer.buffer.indices = { 0,1,2 };
}

void TriangleShader::render(const Camera& camera, const int width, const int height)
{
	{
		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.buffer.modelViewMatrix = camera.getModelViewMatrix();
		renderer.buffer.projectionMatrix = camera.getProjectionMatrix();

		this->renderer.render();
	}
}