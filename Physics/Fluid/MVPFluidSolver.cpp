#include "MVPFluidSolver.h"

#include "MVPMassParticle.h"
#include "MVPVolumeParticle.h"

#include "MVPFluid.h"
#include "MVPSampler.h"

#include "Crystal/Space/CompactSpaceHash.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;
using namespace Crystal::Physics;

MVPFluidSolver::MVPFluidSolver() :
	externalForce(0.0, -9.8f, 0.0),
	buoyancy(0.0f, 0.0f, 0.0f)
{}

void MVPFluidSolver::setupBoundaries()
{
	this->boundarySolver.setup(effectLength);
}

void MVPFluidSolver::clear()
{
	fluids.clear();
	maxTimeStep = 0.03f;
	boundarySolver.clear();
	currentTimeStep = 0;
}

void MVPFluidSolver::addFluidScene(MVPFluid* scene)
{
	this->fluids.push_back(scene);
}

void MVPFluidSolver::setBoundary(const Box3df& box)
{
	this->boundarySolver.clear();
	this->boundarySolver.add(box);
}

void MVPFluidSolver::addBoundaryScene(MVPFluid* scene)
{
	this->boundarySolver.addBoundary(scene);
}

void MVPFluidSolver::simulate()
{
	std::vector<MVPVolumeParticle*> fluidParticles;
	std::list<MVPFluid*> allFluids(this->fluids.begin(), this->fluids.end());

	/*
	for (auto emitter : emitters) {
		emitter->emitParticle(currentTimeStep);
		allFluids.push_back(emitter);
	}
	*/

	if (allFluids.empty()) {
		return;
	}

	/*
	if (currentTimeStep % 5 == 0) {
		MVPSampler sampler;
		sampler.merge(allFluids, effectLength);
	}
	*/

	for (auto fluid : allFluids) {
		const auto ps = fluid->getParticles();
		fluidParticles.insert(fluidParticles.end(), ps.begin(), ps.end());
	}

	for (auto particle : fluidParticles) {
		particle->reset(true);
	}

	if (fluidParticles.empty()) {
		currentTimeStep++;
		return;
	}

	const auto hashSize = fluidParticles.size();
	const auto searchRadius = effectLength;
	CompactSpaceHash spaceHash(searchRadius, static_cast<int>(hashSize));
	for (auto particle : fluidParticles) {
		spaceHash.add(particle->getPosition());
	}

	//boundarySolver.setup(searchRadius);

#pragma omp parallel for
	for (int i = 0; i < fluidParticles.size(); ++i) {
		const auto particle = fluidParticles[i];
		const auto& neighbors = spaceHash.findNeighborIndices(i);
		for (auto n : neighbors) {
			particle->addNeighbor(fluidParticles[n]);
		}
		const auto staticNeighbors = boundarySolver.findNeighbors(particle->getPosition());
		for (auto n : staticNeighbors) {
			particle->addNeighbor(fluidParticles[n]);
		}
	}

	/*
	for (auto particle : fluidParticles) {
		boundarySolver.createGphosts(particle);
	}
	*/

	double time = 0.0;
	while (time < maxTimeStep) {
		const auto dt = calculateTimeStep(fluidParticles);

		for (int i = 0; i < fluidParticles.size(); ++i) {
			const auto particle = fluidParticles[i];
			particle->updateMassPositions();
			particle->updateMassVelocities();
		}

#pragma omp parallel for
		for (int i = 0; i < fluidParticles.size(); ++i) {
			const auto particle = fluidParticles[i];
			particle->updateInnerPoints();
			particle->calculateDensity();
			particle->calculateViscosityForce();
		}


#pragma omp parallel for
		for (int i = 0; i < fluidParticles.size(); ++i) {
			const auto particle = fluidParticles[i];
			//boundarySolver.createMacro(particle);
			boundarySolver.solvePressure(particle, dt);
		}

		for (auto particle : fluidParticles) {
			particle->addForce(externalForce * particle->getDensity());
		}

		// solve incompressibility.
		float relaxationCoe = 1.0f;
		for (int i = 0; i < 2; ++i) {
			for (auto particle : fluidParticles) {
				//				particle->reset(false);
				particle->updateMassPositions();
			}

#pragma omp parallel for
			for (int i = 0; i < fluidParticles.size(); ++i) {
				const auto particle = fluidParticles[i];
				particle->updateInnerPoints();
				//particle->calculateDensity();
				particle->calculatePressureForce(relaxationCoe, dt);
			}
			relaxationCoe *= 0.85f;


			//for (auto particle : fluidParticles) {
			//	solveBoundary(particle, dt);
			//}
			//	solveBoundary(particles);
		}

		for (auto particle : fluidParticles) {
			particle->stepTime(dt);
		}

		time += dt;
	}

	auto densityError = 0.0;
	for (auto particle : fluidParticles) {
		densityError += particle->getDensity() / (double)fluidParticles.size();
	}
	std::cout << densityError << std::endl;

	boundarySolver.clearGphosts();

	/*
	MVPSampler sampler;
	if (currentTimeStep % 2 == 0) {
		sampler.split(allFluids);
	}
	*/

	currentTimeStep++;
}

float MVPFluidSolver::calculateTimeStep(const std::vector<MVPVolumeParticle*>& particles)
{
	float maxVelocity = 0.0f;
	for (auto p : particles) {
		maxVelocity = std::max<float>(maxVelocity, Math::getLengthSquared(p->getVelocity()));
	}
	if (maxVelocity < 1.0e-3) {
		return maxTimeStep;
	}
	maxVelocity = std::sqrt(maxVelocity);
	const auto dt = 0.4f * particles.front()->getRadius() * 2.0f / maxVelocity;
	return maxTimeStep;
	//return std::min(dt, maxTimeStep);
}