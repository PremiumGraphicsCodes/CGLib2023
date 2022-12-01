#pragma once

#include "CGLib/Shader/VertexBuffer.h"
#include "Crystal/Renderer/PointRenderer.h"
#include "Crystal/Scene/Scene/IPresenter.h"

namespace Crystal {
	namespace Physics {
		class SPHVolumeScene;

class SPHVolumePresenter : public Scene::IPresenter
{
public:
	SPHVolumePresenter(SPHVolumeScene* psScene, Crystal::Renderer::PointRenderer* renderer);

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

	SPHVolumeScene* model;
	Crystal::Renderer::PointRenderer* view;
};

	}
}
