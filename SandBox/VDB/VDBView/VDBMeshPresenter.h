#pragma once

#include "CGLib/Shader/VertexBufferObject.h"
#include "Crystal/Renderer/TriangleRenderer.h"

#include "Crystal/Scene/IPresenter.h"

namespace Crystal {
	namespace VDB {
		class VDBMeshScene;

class VDBMeshPresenter : public Scene::IPresenter
{
public:
	VDBMeshPresenter(VDBMeshScene* scene, Crystal::Renderer::TriangleRenderer* renderer) :
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

	VDBMeshScene* model;
	Crystal::Renderer::TriangleRenderer* view;
};

	}
}