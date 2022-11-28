#include "VDBMeshPresenter.h"

#include "VDBMeshScene.h"
#include "../VDB/VDBMesh.h"

#include "CGLib/Shader/VertexBuffer.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

void VDBMeshPresenter::build()
{
	vbo.position.create();
	vbo.color.create();
}

void VDBMeshPresenter::send()
{
	Shader::VertexBuffer<float> position;
	Shader::VertexBuffer<float> color;

	auto shape = model->getShape();

	const auto& vertices = model->getShape()->getVerticesf();
	for (auto& p : vertices) {
		position.add(p);
		color.add(ColorRGBAf(1, 0, 0, 0));
	}

	vbo.position.send(position);
	vbo.color.send(color);

	const auto triangles = model->getShape()->getTriangleFaces();

	for (const auto& tt : triangles) {
		const auto t = tt.indices;
		this->indices.push_back(t[0]);
		this->indices.push_back(t[1]);
		//this->indices.push_back(t[1]);
		this->indices.push_back(t[2]);
	}

	const auto quads = model->getShape()->getQuadFaces();

	for (const auto& qq : quads) {
		const auto q = qq.indices;
		this->indices.push_back(q[0]);
		this->indices.push_back(q[1]);
		//this->indices.push_back(q[1]);
		this->indices.push_back(q[2]);
		//this->indices.push_back(q[2]);
		//this->indices.push_back(q[3]);
	}
}

void VDBMeshPresenter::render(const Camera& camera)
{
	view->buffer.position = &vbo.position;
	view->buffer.color = &vbo.color;
	view->buffer.indices = indices;
	view->buffer.modelViewMatrix = camera.getModelViewMatrix();
	view->buffer.projectionMatrix = camera.getProjectionMatrix();
	//view->buffer.lineWidth = 1.0f;

	view->render();
}
