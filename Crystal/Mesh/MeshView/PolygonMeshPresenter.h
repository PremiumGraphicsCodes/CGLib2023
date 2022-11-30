#pragma once

#include "CGLib/Shader/VertexBuffer.h"
#include "Crystal/Scene/IPresenter.h"
#include "Crystal/Renderer/TriangleRenderer.h"

namespace Crystal {
	namespace Mesh {
		class PolygonMeshScene;

class PolygonMeshPresenter : public Scene::IPresenter
{
public:
	PolygonMeshPresenter(PolygonMeshScene* scene, Crystal::Renderer::TriangleRenderer* renderer) :
		model(scene),
		view(renderer)
	{
	}

	void build() override;

	void send() override;

	void render(const Graphics::Camera& camera) override;

private:
	struct VBO {
		Shader::VertexBufferObject position;
		Shader::VertexBufferObject color;
	};
	VBO vbo;
	std::vector<unsigned int> indices;

	PolygonMeshScene* model;
	Crystal::Renderer::TriangleRenderer* view;
};

	}
}
