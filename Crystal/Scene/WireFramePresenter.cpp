#include "WireFramePresenter.h"

#include "../Scene/WireFrameScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

void WireFramePresenter::build()
{
	vbo.position.create();
	vbo.color.create();
}

void WireFramePresenter::send()
{
	Shader::VertexBuffer<float> position;
	Shader::VertexBuffer<float> color;

	auto shape = model->getShape();
	const auto vertices = shape->getVertices();
	for (auto p : vertices) {
		position.add(p->getPosition());
		color.add(ColorRGBAf(1, 0, 0, 0));
	}

	vbo.position.send(position);
	vbo.color.send(color);
	indices = shape->getIndices();
}

void WireFramePresenter::render(const Camera& camera)
{
	view->buffer.position = &vbo.position;
	view->buffer.color = &vbo.color;
	view->buffer.indices = indices;
	view->buffer.modelViewMatrix = camera.getModelViewMatrix();
	view->buffer.projectionMatrix = camera.getProjectionMatrix();
	view->buffer.lineWidth = 1.0f;

	view->render();
}
