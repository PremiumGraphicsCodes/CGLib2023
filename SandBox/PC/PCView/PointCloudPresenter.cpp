#include "PointCloudPresenter.h"
#include "PointCloudScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::PC;

void PointCloudPresenter::build()
{
	vbo.position.create();
	vbo.size.create();
	vbo.color.create();
}

void PointCloudPresenter::send()
{
	Shader::VertexBuffer<float> position;
	Shader::VertexBuffer<float> color;
	Shader::VertexBuffer<float> size;

	const auto& particles = model->getShape()->getPoints();
	for (auto& p : particles) {
		position.add(p->getPosition());
		color.add(p->getColor());
		size.add(10.0f);
	}

	vbo.position.send(position);
	vbo.color.send(color);
	vbo.size.send(size);

	count = static_cast<int>(particles.size());
}

void PointCloudPresenter::render(const Camera& camera)
{
	view->buffer.position = &vbo.position;
	view->buffer.size = &vbo.size;
	view->buffer.color = &vbo.color;
	view->buffer.count = count;
	view->buffer.modelViewMatrix = camera.getModelViewMatrix();
	view->buffer.projectionMatrix = camera.getProjectionMatrix();

	view->render();
}