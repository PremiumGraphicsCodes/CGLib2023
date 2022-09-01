#include "Renderer.h"

#include "CGLib/Graphics/ColorRGBA.h"
#include "CGLib/Shader/ShaderBuilder.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Shader;
using namespace Crystal::UI;
using namespace Crystal::Renderer;

void Renderer::build()
{
	ShaderBuilder builder;
	builder.buildFromFile("../GLSL/Point.vs", "../GLSL/Point.fs");
	point.setShader(builder.getShader());
	point.link();

	vbo.point.create();
	vbo.color.create();
	vbo.size.create();
}

void Renderer::render(const Camera& camera, ParticleSystemScene* scene)
{
	Buffer buffer;

	const auto ps = scene->getParticles();
	for (auto p : ps) {
		buffer.position.add(p->getPosition());
		buffer.color.add(ColorRGBAf(1, 0, 0, 0));
		buffer.size.add(100);
	}

	vbo.point.send(buffer.position);
	vbo.color.send(buffer.color);
	vbo.size.send(buffer.size);

	point.buffer.position = &vbo.point;
	point.buffer.size = &vbo.size;
	point.buffer.color = &vbo.color;
	point.buffer.count = ps.size();
	point.buffer.modelViewMatrix = camera.getModelViewMatrix();
	point.buffer.projectionMatrix = camera.getProjectionMatrix();

	point.render();
}
