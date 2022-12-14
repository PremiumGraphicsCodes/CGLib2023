#include "MVPFluidEmitter.h"

#include "MVPVolumeParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

MVPFluidEmitter::MVPFluidEmitter() :
	interval(10)
{
}

MVPFluidEmitter::~MVPFluidEmitter()
{
	clearParticles();
}

void MVPFluidEmitter::clearParticles()
{
	for (auto p : particles) {
		delete p;
	}
	particles.clear();
}

void MVPFluidEmitter::emitParticle(const int timeStep)
{
	const auto start = getStartStep();
	const auto end = getEndStep();
	if (start <= timeStep && timeStep <= end) {
		const auto elapsed = timeStep - start;
		if (elapsed % interval == 0) {
			for (const auto& s : seeds) {
				auto mp = create(s.pos, s.radius, s.mass);
				mp->setVelocity(s.velocity);
				mp->setPressureCoe(s.pressureCoe);
				mp->setViscosityCoe(s.viscosityCoe);
				this->particles.push_back(mp);
			}
		}
	}
}

MVPVolumeParticle* MVPFluidEmitter::create(const Vector3df& position, const float radius, const float weight)
{
	auto vp = new MVPVolumeParticle(radius, position);
	auto mp = new MVPMassParticle(vp, Vector3dd(0, 0, 0), weight);
	vp->setRestMass(weight * 1.25f);
	vp->addMassParticle(mp);
	mp->setParent(vp);

	//vp->addMassParticle(mp);
	return vp;
	//	restMass *= 1.5;
	//	selfMass = unum * vnum * wnum * weight;
}

Box3df MVPFluidEmitter::getBoundingBox() const
{
	Box3df bb = Box3df::createDegeneratedBox();
	for (auto p : particles) {
		bb.add(p->getPosition());
	}
	return bb;
}
