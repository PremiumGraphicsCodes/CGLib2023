#pragma once

#include "CGLib/Math/Box3d.h"
#include "IParticle.h"
#include "CGLib/Shape/IShape.h"
#include <vector>
#include <memory>

namespace Crystal {
	namespace Shape {

class ParticleSystem : public IShape
{
public:
	void add(std::unique_ptr<Shape::IParticle> particle);

	const std::vector<std::unique_ptr<IParticle>>& getParticles() const { return particles; }

	Math::Box3df getBoundingBox() const override;

private:
	std::vector<std::unique_ptr<IParticle>> particles;
};

	}
}