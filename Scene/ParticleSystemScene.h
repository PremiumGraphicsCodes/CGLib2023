#pragma once

#include "IScene.h"
#include "IParticle.h"
#include <vector>

namespace Crystal {
	namespace Scene {

class ParticleSystemScene : public IScene
{
public:
	void add(IParticle* particle);

	std::vector<IParticle*> getParticles() const { return particles; }

private:
	std::vector<IParticle*> particles;
};
	}
}