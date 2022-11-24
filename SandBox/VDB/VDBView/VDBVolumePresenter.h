#pragma once

#include "CGLib/Shader/VertexBuffer.h"
#include "Crystal/Scene/IPresenter.h"
#include "Crystal/Renderer/PointRenderer.h"
#include "CGLib/Graphics/ColorMap.h"

namespace Crystal {
	namespace VDB {
		class VDBVolumeScene;

class VDBVolumePresenter : public Scene::IPresenter
{
public:
	VDBVolumePresenter(VDBVolumeScene* psScene, Crystal::Renderer::PointRenderer* renderer) :
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

	Graphics::ColorMap colorMap;
	VDBVolumeScene* model;
	Crystal::Renderer::PointRenderer* view;
};

	}
}
