#pragma once

#include "../Renderer/PointRenderer.h"
#include "../Scene/ParticleSystemScene.h"
#include "CGLib/Shader/VertexBuffer.h"
#include "CGLib/Graphics/Camera.h"
#include "ParticleSystemPresenter.h"

namespace Crystal {
	namespace UI {

class Renderer
{
public:
	void build();

	//void add(ParticleSystemPresenter* presenter) { this->presenters.push_back(presenter); }

	void render(const Graphics::Camera& camera);

	Crystal::Renderer::PointRenderer point;

private:

	//std::vector<ParticleSystemPresenter*> presenters;
};
	}
}
