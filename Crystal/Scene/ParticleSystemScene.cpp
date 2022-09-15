#include "ParticleSystemScene.h"

#include <cassert>

using namespace Crystal::Scene;

ParticleSystemScene::ParticleSystemScene()
{
	//assert(false);
}

void ParticleSystemScene::add(IParticle* particle)
{
	this->particles.push_back(particle);
}
