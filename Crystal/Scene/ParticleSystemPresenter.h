#pragma once

#include "../Renderer/PointRenderer.h"
#include "../Scene/ParticleSystemScene.h"
#include "CGLib/Shader/VertexBuffer.h"
#include "IPresenter.h"

namespace Crystal {
	namespace UI {

class ParticleSystemPresenter : public IPresenter
{
public:
	ParticleSystemPresenter(Scene::ParticleSystemScene* psScene, Crystal::Renderer::PointRenderer* renderer) :
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

	Scene::ParticleSystemScene* model;
	Crystal::Renderer::PointRenderer* view;
};
	}
}
