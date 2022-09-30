#pragma once

#include "SceneBase.h"
#include "CGLib/Shape/IParticle.h"
#include "ParticleSystemPresenter.h"
#include <vector>

namespace Crystal {
	namespace Scene {

class ParticleSystemScene : public SceneBase
{
public:
	ParticleSystemScene();

	void add(Shape::IParticle* particle);

	std::vector<Shape::IParticle*> getParticles() const { return particles; }

	void setPresenter(std::unique_ptr<ParticleSystemPresenter> p) { this->presenter = std::move(p); }

	IPresenter* getPresenter() override { return presenter.get(); }

	Math::Box3df getBoundingBox() const override;

private:
	std::vector<Shape::IParticle*> particles;
	std::unique_ptr<ParticleSystemPresenter> presenter;

};
	}
}