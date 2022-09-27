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
	Shader::VertexBuffer<float> position;
	Shader::VertexBuffer<float> color;

	const auto vertices = model->getVertices();
	for (auto p : vertices) {
		position.add(p->getPosition());
		color.add(ColorRGBAf(1, 0, 0, 0));
	}

	vbo.position.send(position);
	vbo.color.send(color);

	const auto faces = model->getFaces();
	for (const auto& f : faces) {
		indices.push_back(f.v0);
		indices.push_back(f.v1);
		indices.push_back(f.v2);
	}
}

void PolygonMeshPresenter::render(const Camera& camera)
{
	view->buffer.position = &vbo.position;
	view->buffer.color = &vbo.color;
	view->buffer.indices = indices;
	view->buffer.modelViewMatrix = camera.getModelViewMatrix();
	view->buffer.projectionMatrix = camera.getProjectionMatrix();
	//view->buffer.lineWidth = 1.0f;

	view->render();
}