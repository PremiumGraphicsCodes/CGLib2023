#include "CSPHFluidPresenter.h"
#include "CSPHFluidScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

void CSPHFluidPresenter::build()
{
	vbo.position.create();
	vbo.size.create();
	vbo.color.create();
}

void CSPHFluidPresenter::send()
{
	Shader::VertexBuffer<float> position;
	Shader::VertexBuffer<float> color;
	Shader::VertexBuffer<float> size;

	const auto& particles = model->getFluid()->getParticles();
	for (auto& p : particles) {
		position.add(p->getPosition());
		color.add(ColorRGBAf(1, 0, 0, 0));
		size.add(1);
	}

	vbo.position.send(position);
	vbo.color.send(color);
	vbo.size.send(size);

	count = static_cast<int>(particles.size());
}

void CSPHFluidPresenter::render(const Camera& camera)
{
	view->buffer.position = &vbo.position;
	view->buffer.size = &vbo.size;
	view->buffer.color = &vbo.color;
	view->buffer.count = count;
	view->buffer.modelViewMatrix = camera.getModelViewMatrix();
	view->buffer.projectionMatrix = camera.getProjectionMatrix();

	view->render();
}
