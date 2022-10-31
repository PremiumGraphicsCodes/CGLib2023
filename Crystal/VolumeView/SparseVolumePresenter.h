#pragma once

#include "../Renderer/PointRenderer.h"
#include "CGLib/Shader/VertexBuffer.h"
#include "Crystal/Scene/IPresenter.h"

namespace Crystal {
	namespace Volume {
		class SparseVolumeScene;

class SparseVolumePresenter : public Scene::IPresenter
{
public:
	SparseVolumePresenter(SparseVolumeScene* psScene, Crystal::Renderer::PointRenderer* renderer) :
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

	SparseVolumeScene* model;
	Crystal::Renderer::PointRenderer* view;
};

	}
}
