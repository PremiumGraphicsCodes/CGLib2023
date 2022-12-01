#pragma once

#include "Crystal/Scene/SceneBase.h"
#include "ParticleSystem.h"
#include "ParticleSystemPresenter.h"
#include <vector>

namespace Crystal {
	namespace Scene {

class ParticleSystemScene : public SceneBase
{
public:
	ParticleSystemScene();

	void setShape(std::unique_ptr<Shape::ParticleSystem> shape) { this->shape = std::move(shape); }

	Shape::ParticleSystem* getShape() { return shape.get(); }

	Math::Box3df getBoundingBox() const override;

private:
	std::unique_ptr<Shape::ParticleSystem> shape;
};
	}
}