#pragma once

#include "Crystal/Renderer/PointRenderer.h"
#include "CGLib/Shader/VertexBuffer.h"
#include "Crystal/Scene/Scene/IPresenter.h"

namespace Crystal {
	namespace Scene {
		class ParticleSystemScene;

class ParticleSystemIdPresenter : public IPresenter
{
public:
	ParticleSystemIdPresenter(Scene::ParticleSystemScene* psScene, Crystal::Renderer::PointRenderer* renderer) :
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
