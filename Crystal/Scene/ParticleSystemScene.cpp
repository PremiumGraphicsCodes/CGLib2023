#include "ParticleSystemScene.h"

using namespace Crystal::Scene;

void ParticleSystemScene::add(IParticle* particle)
{
	this->particles.push_back(particle);
}
