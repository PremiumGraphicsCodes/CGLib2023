#include "SPHVolumePresenter.h"
#include "SPHVolumeScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Volume;
using namespace Crystal::Physics;

SPHVolumePresenter::SPHVolumePresenter(SPHVolumeScene* psScene, Crystal::Renderer::PointRenderer* renderer) :
	model(psScene),
	view(renderer)
{
}

void SPHVolumePresenter::build()
{
	vbo.position.create();
	vbo.size.create();
	vbo.color.create();
}

void SPHVolumePresenter::send()
{
	Shader::VertexBuffer<float> position;
	Shader::VertexBuffer<float> color;
	Shader::VertexBuffer<float> size;

	const auto& particles = model->getShape()->getNodes();
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

void SPHVolumePresenter::render(const Graphics::Camera& camera)
{
	view->buffer.position = &vbo.position;
	view->buffer.size = &vbo.size;
	view->buffer.color = &vbo.color;
	view->buffer.count = count;
	view->buffer.modelViewMatrix = camera.getModelViewMatrix();
	view->buffer.projectionMatrix = camera.getProjectionMatrix();

	view->render();
}