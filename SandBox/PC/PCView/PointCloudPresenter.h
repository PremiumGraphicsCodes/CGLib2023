#pragma once

#include "CGLib/Shader/VertexBuffer.h"
#include "Crystal/Scene/Scene/IPresenter.h"
#include "Crystal/Renderer/PointRenderer.h"

namespace Crystal {
	namespace PC {
		class PointCloudScene;

class PointCloudPresenter : public Scene::IPresenter
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

	PointCloudScene* model;
	Crystal::Renderer::PointRenderer* view;
};

	}
}
