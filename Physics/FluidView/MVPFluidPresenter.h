#pragma once

#include "CGLib/Shader/VertexBuffer.h"
#include "Crystal/Scene/Scene/IPresenter.h"
#include "Crystal/Renderer/PointRenderer.h"

namespace Crystal {
	namespace Physics {
		class MVPFluidScene;

class MVPFluidPresenter : public Scene::IPresenter
{
public:
	MVPFluidPresenter(MVPFluidScene* scene, Crystal::Renderer::PointRenderer* renderer) :
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
		Shader::VertexBufferObject size;
	};
	VBO vbo;
	int count;

	MVPFluidScene* model;
	Crystal::Renderer::PointRenderer* view;
};

	}
}
