#pragma once

#include "../Renderer/PointRenderer.h"
#include "../Scene/ParticleSystemScene.h"
#include "CGLib/Shader/VertexBuffer.h"


namespace Crystal {
	namespace UI {

class ParticleSystemPresenter
{
public:
	ParticleSystemPresenter(Scene::ParticleSystemScene* psScene, Crystal::Renderer::PointRenderer* renderer) :
		model(psScene),
		view(renderer)
	{
	}

	void build();

	void send();

	void render();

private:
	struct Buffer {
		Shader::VertexBuffer<float> position;
		Shader::VertexBuffer<float> color;
		Shader::VertexBuffer<float> size;
	};

	Buffer buffer;

	Scene::ParticleSystemScene* model;
	Crystal::Renderer::PointRenderer* view;
};
	}
}
