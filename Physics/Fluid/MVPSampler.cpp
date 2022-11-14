#include "MVPSampler.h"

#include "MVPFluid.h"
#include "MVPVolumeParticle.h"
#include "Crystal/Space/Space/CompactSpaceHash.h"
#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Physics;

void MVPSampler::split(const std::list<MVPFluid*>& fluids)
{
	for (auto f : fluids) {
		const auto fps = f->getParticles();
		std::vector<MVPVolumeParticle*> ps;
		for (auto p : fps) {
			if (p->getDensity() < 0.75) {
				ps.push_back(p);
			}
		}
		for (auto p : ps) {
			const auto masses = p->getMassParticles();
			for (auto m : masses) {
				MVPVolumeParticle* vp = new MVPVolumeParticle(p->getRadius() * 0.50f, m->getPosition());
				vp->setVelocity(m->getVelocity());
				vp->addMassParticle(m);
				m->setParent(vp);
				vp->setRestMass(m->getMass() * 1.25f);
				f->add(vp);
			}
			p->clearMasses();
		}
	}

	for (auto f : fluids) {
		f->removeDegeneratedVolumes();
	}
}

void MVPSampler::merge(const std::list<MVPFluid*>& fluids, const double searchRadius)
{
	std::vector<MVPVolumeParticle*> tinyParticles;
	for (auto fluid : fluids) {
		const auto fps = fluid->getParticles();
		for (auto p : fps) {
			if (p->getMassParticles().size() == 1) {
				tinyParticles.push_back(p);
			}
		}
		CompactSpaceHash spaceHash(searchRadius * 0.5, static_cast<int>(tinyParticles.size()));
		for (auto p : tinyParticles) {
			spaceHash.add(p->getPosition());
		}
		for (auto p : tinyParticles) {
			const auto neighbors = spaceHash.findNeighborIndices(p->getPosition());
			if (neighbors.size() >= 8) {
				//std::cout << "IsAbleToMerge" << std::endl;
				//auto target = static_cast<MVPVolumeParticle*>(p);
				Vector3df newPosition(0, 0, 0);
				Vector3df newVelocity(0, 0, 0);
				std::vector<MVPMassParticle*> masses;
				float r = 0.0;
				for (int i = 0; i < 8; ++i) {
					auto n = tinyParticles[neighbors[i]];
					//fluid = n->
					r = n->getRadius();
					auto m = n->getMassParticles().front();
					masses.push_back(m);
					//target->addMassParticle(m);
					//m->setParent(target);
					n->clearMasses();
					newPosition += n->getPosition();
					newVelocity += n->getVelocity();
					spaceHash.remove(neighbors[i]);
				}
				newPosition /= 8.0f;
				newVelocity /= 8.0f;
				MVPVolumeParticle* target = new MVPVolumeParticle(r * 2.0f, newPosition);
				target->setVelocity(newVelocity);
				for (auto m : masses) {
					target->addMassParticle(m);
					m->setParent(target);
				}
				target->setRestMass(masses[0]->getMass() * 8.0f * 1.25f);
				fluid->add(target);
			}
		}
	}
	for (auto f : fluids) {
		f->removeDegeneratedVolumes();
	}

}