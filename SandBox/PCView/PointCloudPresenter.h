#pragma once

#include "CGLib/Shader/VertexBuffer.h"
#include "Crystal/Scene/IPresenter.h"
#include "Crystal/Renderer/PointRenderer.h"

namespace Crystal {
	namespace Scene {
		class PointCloudScene;

class PointCloudPresenter : public IPresenter
{
public:
	PointCloudPresenter(PointCloudScene* psScene, Crystal::Renderer::PointRenderer* renderer) :
		model(psScene),
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
		Shader::VertexBufferObject size;
	};
	VBO vbo;
	int count;

	Scene::PointCloudScene* model;
	Crystal::Renderer::PointRenderer* view;
};

	}
}
