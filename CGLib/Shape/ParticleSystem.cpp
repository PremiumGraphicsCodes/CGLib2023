#include "ParticleSystem.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

void ParticleSystem::add(IParticle* particle)
{
	this->particles.push_back(particle);
}

Box3df ParticleSystem::getBoundingBox() const
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
