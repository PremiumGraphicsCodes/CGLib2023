#pragma once

#include "IScene.h"
#include "IParticle.h"
#include "ParticleSystemPresenter.h"
#include <vector>

namespace Crystal {
	namespace Scene {

class ParticleSystemScene : public IScene
{
public:
	ParticleSystemScene();

	void add(IParticle* particle);

	std::vector<IParticle*> getParticles() const { return particles; }

	void setPresenter(std::unique_ptr<ParticleSystemPresenter> p) { this->presenter = std::move(p); }

	IPresenter* getPresenter() { return presenter.get(); }

private:
	std::vector<IParticle*> particles;
	std::unique_ptr<ParticleSystemPresenter> presenter;

};
	}
}