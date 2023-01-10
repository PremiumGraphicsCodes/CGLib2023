#pragma once

#include "CGLib/Shader/VertexBuffer.h"
#include "Crystal/Scene/Scene/IPresenter.h"
#include "Crystal/Renderer/Renderer/PointRenderer.h"
#include "CGLib/Graphics/ColorMap.h"

namespace Crystal {
	namespace UI {
		class BoundaryScene;

class BoundaryPresenter : public Scene::IPresenter
{
public:
	BoundaryPresenter(BoundaryScene* psScene, Crystal::Renderer::PointRenderer* renderer) :
		model(psScene),
		view(renderer)
	{
	}

	void build() override;

	void send() override;

	void render(const Graphics::Camera& camera) override;

	void setMinMax(const float min, const float max) { this->colorMap.setMinMax(min, max); }

private:
	struct VBO {
		Shader::VertexBufferObject position;
		Shader::VertexBufferObject color;
		Shader::VertexBufferObject size;
	};
	VBO vbo;
	int count;

	BoundaryScene* model;
	Crystal::Renderer::PointRenderer* view;
	Graphics::ColorMap colorMap;
};

	}
}
