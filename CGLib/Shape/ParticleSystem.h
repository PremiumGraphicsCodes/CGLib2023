#pragma once

#include "../Math/Box3d.h"
#include "IParticle.h"
#include <vector>

namespace Crystal {
	namespace Shape {

class ParticleSystem
{
public:
	void add(Shape::IParticle* particle);

	std::vector<Shape::IParticle*> getParticles() const { return particles; }

	Math::Box3df getBoundingBox() const;

private:

	std::vector<Shape::IParticle*> particles;
};

	}
}