#include "PolygonMeshPresenter.h"

#include "../Scene/PolygonMeshScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

void PolygonMeshPresenter::build()
{
	vbo.position.create();
	vbo.color.create();
}

void PolygonMeshPresenter::send()
{
	/*
	Shader::VertexBuffer<float> position;
	Shader::VertexBuffer<float> color;

	const auto vertices = model->getVertices();
	for (auto p : vertices) {
		position.add(p->getPosition());
		color.add(ColorRGBAf(1, 0, 0, 0));
	}

	vbo.position.send(position);
	vbo.color.send(color);
	indices = model->getIndices();
	*/
}

void PolygonMeshPresenter::render(const Camera& camera)
{
	/*
	view->buffer.position = &vbo.position;
	view->buffer.color = &vbo.color;
	view->buffer.indices = indices;
	view->buffer.modelViewMatrix = camera.getModelViewMatrix();
	view->buffer.projectionMatrix = camera.getProjectionMatrix();
	view->buffer.lineWidth = 1.0f;

	view->render();
	*/
}
