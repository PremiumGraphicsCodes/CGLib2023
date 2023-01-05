#include "MVPFluid.h"

#include "MVPVolumeParticle.h"

#include <algorithm>
#include <iterator>
#include <random>

using namespace Crystal::Math;
using namespace Crystal::Physics;

MVPFluid::MVPFluid()
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
}

MVPVolumeParticle* MVPFluid::create(const Vector3df& position, const float radius, const float weight)
{
	auto vp = new MVPVolumeParticle(radius, position);
	auto mp = new MVPMassParticle(vp, Vector3dd(0, 0, 0), weight / 3.0);
	vp->setRestMass(weight * 2.0);
	vp->addMassParticle(mp);
	mp->setParent(vp);

	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<float> dist(-1.0, 1.0);

	{
		const auto x = dist(mt);
		const auto y = dist(mt);
		const auto z = dist(mt);
		Vector3df v(x, y, z);
		v = glm::normalize(v);
		auto mp1 = new MVPMassParticle(vp, v, weight / 3.0);
		vp->addMassParticle(mp1);
		mp1->setParent(vp);
		auto mp2 = new MVPMassParticle(vp, -v, weight / 3.0);
		vp->addMassParticle(mp2);
		mp2->setParent(vp);
	}
	return vp;
}