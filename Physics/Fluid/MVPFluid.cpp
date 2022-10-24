#include "MVPFluid.h"

#include "MVPVolumeParticle.h"

#include <algorithm>
#include <iterator>


using namespace Crystal::Math;
using namespace Crystal::Physics;

MVPFluid::MVPFluid() :
	pressureCoe(10000.0),
	viscosityCoe(50.0)
{
}

MVPFluid::~MVPFluid()
{
}

Box3df MVPFluid::getBoundingBox() const
{
	Box3df bb = Box3df::createDegeneratedBox();
	for (auto p : particles) {
		bb.add(p->getPosition());
	}
	return bb;
}

void MVPFluid::removeDegeneratedVolumes()
{
	this->particles.sort();
	std::list<MVPVolumeParticle*> vps;
	for (auto v : particles) {
		if (v->getMassParticles().empty()) {
			vps.push_back(v);
		}
	}
	std::list<MVPVolumeParticle*> diffs;
	std::set_difference(
		this->particles.begin(), this->particles.end(),
		vps.begin(), vps.end(),
		std::inserter(diffs, diffs.end())
	);
	this->particles = diffs;
	for (auto v : vps) {
		delete v;
	}
	removeExpired();
}

void MVPFluid::removeExpired()
{
	std::list<MVPVolumeParticle*> vps;
	if (lifeLimit != -1) {
		for (auto v : particles) {
			if (v->getMassParticles().front()->lifeTime > lifeLimit) {
				v->clearMasses();
				vps.push_back(v);
			}
		}
	}
	std::list<MVPVolumeParticle*> diffs;
	std::set_difference(
		this->particles.begin(), this->particles.end(),
		vps.begin(), vps.end(),
		std::inserter(diffs, diffs.end())
	);
	this->particles = diffs;
	for (auto v : vps) {
		delete v;
	}
}

MVPVolumeParticle* MVPFluid::create(const Vector3df& position, const float radius, const float weight, const float temperature)
{
	auto vp = new MVPVolumeParticle(radius, position);
	auto mp = new MVPMassParticle(vp, Vector3dd(0, 0, 0), weight);
	mp->updateTemperature(1000.0f);
	vp->setRestMass(weight * 1.25f);
	vp->addMassParticle(mp);
	mp->setParent(vp);

	//vp->addMassParticle(mp);
	return vp;
	//	restMass *= 1.5;
	//	selfMass = unum * vnum * wnum * weight;
}