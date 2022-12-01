#pragma once

#include "CGLib/Shader/VertexBuffer.h"
#include "Crystal/Scene/Scene/IPresenter.h"
#include "Crystal/Renderer/PointRenderer.h"

namespace Crystal {
	namespace VDB {
		class VDBPointsScene;

class VDBPointsPresenter : public Scene::IPresenter
{
public:
	VDBPointsPresenter(VDBPointsScene* psScene, Crystal::Renderer::PointRenderer* renderer) :
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

	VDBPointsScene* model;
	Crystal::Renderer::PointRenderer* view;
};

	}
}
