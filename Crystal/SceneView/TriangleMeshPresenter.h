#pragma once

#include "../Renderer/TriangleRenderer.h"
#include "CGLib/Shader/VertexBuffer.h"
#include "Crystal/Scene/IPresenter.h"

namespace Crystal {
	namespace Scene {
		class TriangleMeshScene;

class TriangleMeshPresenter : public IPresenter
{
public:
	TriangleMeshPresenter(Scene::TriangleMeshScene* scene, Crystal::Renderer::TriangleRenderer* renderer) :
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

	Scene::TriangleMeshScene* model;
	Crystal::Renderer::TriangleRenderer* view;
};

	}
}
