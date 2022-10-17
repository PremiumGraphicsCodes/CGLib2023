#include "PBLightShader.h"

#include "CGLib/Shader/TextureObject.h"

#include "CGLib/Shader/ShaderBuilder.h"
#include "CGLib/Shader/VertexBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Renderer;

void PBLightShader::build()
{
	ShaderBuilder builder;
	builder.buildFromFile("../GLSL/PBLight.vs", "../GLSL/PBLight.fs");
	renderer.setShader(builder.getShader());
	renderer.link();

	VertexBuffer<float> vb;
	vb.add(Vector3df(0.0, 0.0, 0.0));
	vb.add(Vector3df(1.0, 0.0, 0.0));
	vb.add(Vector3df(1.0, 1.0, 0.0));
	vb.add(Vector3df(0.0, 1.0, 0.0));

	VertexBuffer<float> nb;
	nb.add(Vector3df(0, 0, 1));
	nb.add(Vector3df(0, 0, 1));
	nb.add(Vector3df(0, 0, 1));
	nb.add(Vector3df(0, 0, 1));

	positions.create();
	normals.create();

	positions.send(vb.getData());
	normals.send(nb.getData());

	renderer.buffer.position = &positions;
	renderer.buffer.normal = &normals;

	renderer.buffer.indices.push_back(0);
	renderer.buffer.indices.push_back(1);
	renderer.buffer.indices.push_back(2);

	renderer.buffer.indices.push_back(0);
	renderer.buffer.indices.push_back(2);
	renderer.buffer.indices.push_back(3);

	renderer.buffer.lightPosition = Vector3dd(1, 1, 1);
	renderer.buffer.lightColor = Vector3dd(1, 1, 1);

	renderer.buffer.albedo = Vector3dd(1, 1, 1);
	renderer.buffer.roughness = 0.1;
	renderer.buffer.metalic = 0.1;
	renderer.buffer.ao = 0.1;
}

void PBLightShader::render(const Camera& camera, const int width, const int height)
{
	{
		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.buffer.modelMatrix = camera.getModelMatrix();
		renderer.buffer.viewMatrix = camera.getViewMatrix();
		renderer.buffer.projectionMatrix = camera.getProjectionMatrix();
		renderer.buffer.eyePosition = camera.getEye();

		this->renderer.render();
	}
}