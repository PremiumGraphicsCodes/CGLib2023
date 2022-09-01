#pragma once

#include "../Renderer/LineRenderer.h"
#include "../Scene/WireFrameScene.h"
#include "CGLib/Shader/VertexBuffer.h"
#include "IPresenter.h"

namespace Crystal {
	namespace UI {

class WireFramePresenter : public IPresenter
{
public:
	WireFramePresenter(Scene::WireFrameScene* psScene, Crystal::Renderer::LineRenderer* renderer) :
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
	};
	VBO vbo;
	std::vector<unsigned int> indices;

	Scene::WireFrameScene* model;
	Crystal::Renderer::LineRenderer* view;
};

	}
}
