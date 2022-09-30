#include "ParticleSystemScene.h"

#include <cassert>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;

ParticleSystemScene::ParticleSystemScene()
{
	//assert(false);
}

void ParticleSystemScene::add(IParticle* particle)
{
	this->particles.push_back(particle);
}

Box3df ParticleSystemScene::getBoundingBox() const
{
	if (particles.empty()) {
		return Box3df::createDegeneratedBox();
	}
	Math::Box3df bb(particles.front()->getPosition());
	for (auto p : particles) {
		bb.add(p->getPosition());
	}
	return bb;
}