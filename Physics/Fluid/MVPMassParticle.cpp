#include "MVPMassParticle.h"

#include "MVPVolumeParticle.h"
#include "MVPFluid.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

MVPMassParticle::MVPMassParticle(MVPVolumeParticle* parent, const Math::Vector3df& point, const float mass) :
	parent(parent),
	vector(point),
	mass(mass)
{
	updatePosition(parent->getPosition());
	updateVelocity(parent->getVelocity());
}


Vector3df MVPMassParticle::getPosition() const
{
	return position;
}

Vector3df MVPMassParticle::getVelocity() const
{
	return velocity;
}

void MVPMassParticle::updatePosition(const Vector3df& parentPosition)
{
	this->position = parentPosition + parent->getRadius() * vector;
}

void MVPMassParticle::updateVelocity(const Vector3df& parentVelocity)
{
	this->velocity = parentVelocity;
}