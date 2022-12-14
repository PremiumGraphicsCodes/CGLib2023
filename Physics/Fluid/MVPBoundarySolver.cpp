#include "MVPBoundarySolver.h"

#include "MVPVolumeParticle.h"
#include "MVPFluid.h"

using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Physics;

void MVPBoundarySolver::setup(const float effectLength)
{
	std::vector<MVPVolumeParticle*> boundaryParticles;
	for (auto b : boundaries) {
		const auto bp = b->getParticles();
		boundaryParticles.insert(boundaryParticles.end(), bp.begin(), bp.end());
	}

	if (boundaryParticles.empty()) {
		return;
	}

	const auto hashSize = boundaryParticles.front()->getPoints().size() * boundaryParticles.size();
	const auto searchRadius = effectLength;
	spaceHash = std::make_unique<CompactSpaceHash>(searchRadius, static_cast<int>(boundaryParticles.size()));
	//spaceHash.setup(searchRadius, boundaryParticles.size());

	for (auto bp : boundaryParticles) {
		spaceHash->add(bp->getPosition());
		/*
		const auto& microParticles = bp->getPoints();
		for (auto mp : microParticles) {
			spaceHash->add(mp);
		}
		*/
	}
}

std::vector<int> MVPBoundarySolver::findNeighbors(const Vector3df& position)
{
	if (spaceHash == nullptr) {
		return {};
	}
	return spaceHash->findNeighborIndices(position);
}

/*
MVPVolumeParticle* MVPBoundarySolver::createGphost(const Vector3df& p, MVPVolumeParticle* particle)
{
	const auto radius = particle->getRadius();
	auto massP = particle->getMassParticles().front();
	const auto mass = massP->getMass();

	auto vp = new MVPVolumeParticle(radius, p);
	if (particle->getMassParticles().size() == 1) {
		MVPMassParticle* mp = new MVPMassParticle(vp, Vector3df(0, 0, 0), mass);
		mp->setParent(vp);
		vp->addMassParticle(mp);
	}
	else {
		const auto e = 1.0e-12;
		for (float x = -radius; x < radius + e; x += radius * 2.0f) {
			for (float y = -radius; y < radius + e; y += radius * 2.0f) {
				for (float z = -radius; z < radius + e; z += radius * 2.0f) {
					MVPMassParticle* mp = new MVPMassParticle(vp, Vector3df(x, y, z), mass * 8.0f);
					mp->setParent(vp);
					vp->addMassParticle(mp);
				}
			}
		}
	}
	vp->setPressureCoe(massP->getPressureCoe());
	vp->setViscosityCoe(massP->getViscosityCoe());

	return vp;
}
*/

/*
void MVPBoundarySolver::createGphosts(MVPVolumeParticle* particle)
{
	const auto r = particle->getRadius();
	for (const auto& csg : csgBoundaries) {
		for (const auto& boundary : csg->getBoxes()) {
			auto position = particle->getPosition();
			if (position.y < boundary.getMinY() - r) {
				position.y = boundary.getMinY() - r;
				auto vp = createGphost(position, particle);
				particle->addNeighbor(vp);
				this->ghosts.push_back(vp);
			}
			if (position.y > boundary.getMaxY() + r) {
				const auto distance = boundary.getMinY() + r;
				auto vp = createGphost(position, particle);
				particle->addNeighbor(vp);
				this->ghosts.push_back(vp);
			}
			if (position.x > boundary.getMaxX() + r) {
				const auto distance = boundary.getMinX() + r;
				auto vp = createGphost(position, particle);
				particle->addNeighbor(vp);
				this->ghosts.push_back(vp);
			}
			if (position.x < boundary.getMinX() - r) {
				const auto distance = boundary.getMinX() - r;
				auto vp = createGphost(position, particle);
				particle->addNeighbor(vp);
				this->ghosts.push_back(vp);
			}
			if (position.z > boundary.getMaxZ() + r) {
				const auto distance = boundary.getMaxZ() + r;
				auto vp = createGphost(position, particle);
				particle->addNeighbor(vp);
				this->ghosts.push_back(vp);
			}
			if (position.z < boundary.getMinZ() - r) {
				const auto distance = boundary.getMinZ() - r;
				const auto overlap = Vector3dd(0, 0, distance);
				auto vp = createGphost(position, particle);
				particle->addNeighbor(vp);
				this->ghosts.push_back(vp);
			}
		}
	}
}
*/

void MVPBoundarySolver::clearGphosts()
{
	for (auto g : ghosts) {
		delete g;
	}
	ghosts.clear();
}

void MVPBoundarySolver::solvePressure(MVPVolumeParticle* particle, const double dt)
{
	for (const auto& boundary : csgBoundaries) {
		const auto min = boundary.getMin();
		const auto max = boundary.getMax();
		const auto position = particle->getAveragedCenter();
		if (position.y < min.y) {
			const auto distance = min.y - position.y;
			const auto overlap = Vector3dd(0, distance, 0);
			particle->addForce(overlap / dt / dt);
//			particle->addDx(overlap);
		}
		if (position.y > max.y) {
			const auto distance = max.y - position.y;
			const auto overlap = Vector3dd(0, distance, 0);
			particle->addForce(overlap / dt / dt);
			//particle->addDx(overlap);
		}
		if (position.x > max.x) {
			const auto distance = max.x - position.x;
			const auto overlap = Vector3dd(distance, 0, 0);
			particle->addForce(overlap / dt / dt);
//			particle->addDx(overlap);
		}
		if (position.x < min.x) {
			const auto distance = min.x - position.x;
			const auto overlap = Vector3dd(distance, 0, 0);
			particle->addForce(overlap / dt / dt);
//			particle->addDx(overlap);
		}
		if (position.z > max.z) {
			const auto distance = max.z - position.z;
			const auto overlap = Vector3dd(0, 0, distance);
			particle->addForce(overlap / dt / dt);
//			particle->addDx(overlap);
		}
		if (position.z < min.z) {
			const auto distance = min.z - position.z;
			const auto overlap = Vector3dd(0, 0, distance);
			particle->addForce(overlap / dt / dt);
//			particle->addDx(overlap);
		}
	}
}