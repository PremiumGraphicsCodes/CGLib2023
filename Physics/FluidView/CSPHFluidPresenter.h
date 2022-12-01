#pragma once

#include "CGLib/Shader/VertexBuffer.h"
#include "Crystal/Scene/Scene/IPresenter.h"
#include "Crystal/Renderer/PointRenderer.h"

namespace Crystal {
	namespace Physics {
		class CSPHFluidScene;

class CSPHFluidPresenter : public Scene::IPresenter
{
public:
	CSPHFluidPresenter(CSPHFluidScene* psScene, Crystal::Renderer::PointRenderer* renderer) :
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

	CSPHFluidScene* model;
	Crystal::Renderer::PointRenderer* view;
};
	}
}
