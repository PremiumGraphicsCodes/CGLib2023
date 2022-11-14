#include "PointShader.h"
#include "Crystal/Renderer/PointShaderSource.h"

#include "CGLib/Shader/ShaderBuilder.h"
#include "CGLib/Shader/VertexBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Renderer;

void PointShader::build()
{
	ShaderBuilder builder;
	builder.build(PointShaderSource::getVertexShaderSource(), PointShaderSource::getFragmentShaderSource());
	renderer.setShader(builder.getShader());
	renderer.link();

	VertexBuffer<float> vb;
	vb.add(Vector3df(0.0, 0.0, 0.0));
	vb.add(Vector3df(0.1, 0.0, 0.0));
	vb.add(Vector3df(0.1, 0.1, 0.0));
	vb.add(Vector3df(0.0, 0.1, 0.0));

	VertexBuffer<float> colorBuffer;
	colorBuffer.add(ColorRGBAf(1, 0, 0, 1));
	colorBuffer.add(ColorRGBAf(0, 1, 0, 1));
	colorBuffer.add(Vector3df(0, 0, 1));
	colorBuffer.add(Vector3df(0, 0, 1));

	VertexBuffer<float> sizeBuffer;
	sizeBuffer.add(100.0f);
	sizeBuffer.add(100.0f);
	sizeBuffer.add(100.0f);
	sizeBuffer.add(100.0f);

	positions.create();
	colors.create();
	sizes.create();

	positions.send(vb.getData());
	colors.send(colorBuffer.getData());
	sizes.send(sizeBuffer.getData());

	renderer.buffer.position = &positions;
	renderer.buffer.color = &colors;
	renderer.buffer.size = &sizes;

	renderer.buffer.count = 4;
}

void PointShader::render(const Camera& camera, const int width, const int height)
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