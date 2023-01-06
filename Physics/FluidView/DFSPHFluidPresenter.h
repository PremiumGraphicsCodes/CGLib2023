#pragma once

#include "CGLib/Shader/VertexBuffer.h"
#include "Crystal/Scene/Scene/IPresenter.h"
#include "Crystal/Renderer/Renderer/PointRenderer.h"
#include "CGLib/Graphics/ColorMap.h"

namespace Crystal {
	namespace Physics {
		class DFSPHFluidScene;

class DFSPHFluidPresenter : public Scene::IPresenter
{
public:
	DFSPHFluidPresenter(DFSPHFluidScene* psScene, Crystal::Renderer::PointRenderer* renderer) :
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

	DFSPHFluidScene* model;
	Crystal::Renderer::PointRenderer* view;
	Graphics::ColorMap colorMap;
};

	}
}
