#pragma once

#include "Crystal/Scene/SceneBase.h"
#include "CGLib/Shape/ParticleSystem.h"
#include "ParticleSystemPresenter.h"
#include <vector>

namespace Crystal {
	namespace Scene {

class ParticleSystemScene : public SceneBase
{
public:
	ParticleSystemScene();

	void setShape(std::unique_ptr<Shape::ParticleSystem> shape) { this->shape = std::move(shape); }

	void setPresenter(std::unique_ptr<ParticleSystemPresenter> p) { this->presenter = std::move(p); }

	Shape::ParticleSystem* getShape() { return shape.get(); }

	IPresenter* getPresenter() override { return presenter.get(); }

	Math::Box3df getBoundingBox() const override;

private:
	std::unique_ptr<Shape::ParticleSystem> shape;
	std::unique_ptr<ParticleSystemPresenter> presenter;

};
	}
}