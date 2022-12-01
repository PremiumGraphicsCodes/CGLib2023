#pragma once

#include "CGLib/Shader/VertexBuffer.h"
#include "Crystal/Scene/Scene/IPresenter.h"
#include "Crystal/Renderer/PointRenderer.h"

namespace Crystal {
	namespace Physics {
		class PBSPHFluidScene;

class PBSPHFluidPresenter : public Scene::IPresenter
{
public:
	PBSPHFluidPresenter(PBSPHFluidScene* psScene, Crystal::Renderer::PointRenderer* renderer) :
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

	PBSPHFluidScene* model;
	Crystal::Renderer::PointRenderer* view;
};

	}
}
