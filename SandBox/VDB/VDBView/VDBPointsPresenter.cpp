#include "VDBPointsPresenter.h"
#include "VDBPointsScene.h"

#include "../VDB/VDBPoints.h"

using namespace Crystal::Graphics;
using namespace Crystal::VDB;

void VDBPointsPresenter::build()
{
	vbo.position.create();
	vbo.size.create();
	vbo.color.create();
}

void VDBPointsPresenter::send()
{
	Shader::VertexBuffer<float> position;
	Shader::VertexBuffer<float> color;
	Shader::VertexBuffer<float> size;

	const auto& particles = model->getShape()->getPositions();
	for (auto& p : particles) {
		position.add(p);
		color.add(ColorRGBAf(1,0,0,0));
		size.add(10.0f);
	}

	vbo.position.send(position);
	vbo.color.send(color);
	vbo.size.send(size);

	count = static_cast<int>(particles.size());
}

void VDBPointsPresenter::render(const Camera& camera)
{
	view->buffer.position = &vbo.position;
	view->buffer.size = &vbo.size;
	view->buffer.color = &vbo.color;
	view->buffer.count = count;
	view->buffer.modelViewMatrix = camera.getModelViewMatrix();
	view->buffer.projectionMatrix = camera.getProjectionMatrix();

	view->render();
}
