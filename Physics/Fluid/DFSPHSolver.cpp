#include "DFSPHSolver.h"
#include "DFSPHParticle.h"
#include "DFSPHFluid.h"
#include "DFSPHBoundarySolver.h"

#include "Crystal/Space/Space/CompactSpaceHash.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Physics;

DFSPHSolver::DFSPHSolver() :
	maxTimeStep(0.01f)
{}

/*
void DFFluidSolver::step()
{
	simulate(maxTimeStep, 2.25, 2.5, 3);
}
*/

void DFSPHSolver::simulate(const float searchLength, const int maxIter)
{
	std::vector<DFSPHParticle*> particles;
	for (auto fluid : fluids) {
		const auto& ps = fluid->getParticles();
		//particles.insert(particles.end(), ps.begin(), ps.end());
		for (auto& p : ps) {
			particles.push_back(p.get());
		}
	}


	/*
	for (auto p : particles) {
		p->init();
	}
	*/

	const auto hashSize = static_cast<int>(particles.size()) * 2;
	const auto searchRadius = particles.front()->getRadius() * 2.25;
	CompactSpaceHash spaceHash1(searchRadius, hashSize);
	for (auto particle : particles) {
		particle->clearNeighbors();
		spaceHash1.add(particle->getPosition());
	}

#pragma omp parallel for
	for (int i = 0; i < particles.size(); ++i) {
		auto particle = particles[i];
		const auto& neighbors = spaceHash1.findNeighborIndices(i);
		for (auto mp : neighbors) {
			particle->addNeighbor(particles[mp]);
		}
	}

#pragma omp parallel for
	for (int i = 0; i < particles.size(); ++i) {
		particles[i]->calculateDensity();
		particles[i]->calculateAlpha();
	}

	// compute factor alpha.

	auto time = 0.0;
	while (time < maxTimeStep) {
		for (int i = 0; i < particles.size(); ++i) {
			particles[i]->force = Vector3df(0.0f, 0.0f, 0.0f);
			particles[i]->force += Vector3df(0.0, -9.8, 0.0) * particles[i]->getMass();
		}

		for (int i = 0; i < particles.size(); ++i) {
			particles[i]->calculateViscosity();
		}

		const auto dt = calculateTimeStep(particles);
		DFSPHBoundarySolver boundarySolver(dt, boundary);
		boundarySolver.solve(particles);

		for (int i = 0; i < particles.size(); ++i) {
			particles[i]->velocity += dt * particles[i]->force / particles[i]->getMass();
		}
		correctDensityError(particles, dt);

		for (int i = 0; i < particles.size(); ++i) {
			particles[i]->position += dt * particles[i]->getVelocity();
		}

#pragma omp parallel for
		for (int i = 0; i < particles.size(); ++i) {
			particles[i]->calculateDensity();
			particles[i]->calculateAlpha();
		}

		correctDivergenceError(particles, dt);
		time += dt;
	}

	auto densityError = 0.0;
	for (auto particle : particles) {
		densityError += particle->getDensity() / (double)particles.size();
	}
	std::cout << densityError << std::endl;

}

void DFSPHSolver::correctDivergenceError(const std::vector<DFSPHParticle*>& particles, const float dt)
{
	bool isErrorOk = false;
	int iter = 0;
	while ((!isErrorOk || iter < 1) && iter < 100) {
		for (int i = 0; i < particles.size(); ++i) {
			particles[i]->calculateDpDt();
		}
		for (int i = 0; i < particles.size(); ++i) {
			particles[i]->calculateVelocityInDivergenceError(dt);
		}
		const auto averageDpDt = calculateAverageDpDt(particles);
		isErrorOk = averageDpDt < 2.0f;
		iter++;
	}
}

void DFSPHSolver::correctDensityError(const std::vector<DFSPHParticle*>& particles, const float dt)
{
	bool isErrorOk = false;
	auto iter = 0;
	while ((!isErrorOk || iter < 2) && iter < 100) {
		const auto restDensity = particles.front()->getDensity();

		//particles.front()->getDensity()
		for (int i = 0; i < particles.size(); ++i) {
			particles[i]->predictDensity(dt);
		}
		for (int i = 0; i < particles.size(); ++i) {
			particles[i]->calculateVelocityInDensityError(dt);
		}

		const auto averageDensity = calculateAverageDensity(particles);
		const auto densityErrorRatio = ::fabs(averageDensity - restDensity) / restDensity;
		isErrorOk = densityErrorRatio < 0.05;

		iter++;
	}
}

float DFSPHSolver::calculateTimeStep(const std::vector<DFSPHParticle*>& particles)
{
	float maxVelocity = 0.0;
	for (auto p : particles) {
		maxVelocity = std::max<float>(maxVelocity, Math::getLengthSquared(p->getVelocity()));
	}
	if (maxVelocity < 1.0e-3) {
		return maxTimeStep / 2.0f;
	}
	maxVelocity = std::sqrt(maxVelocity);
	const auto dt = 0.4f * particles.front()->getRadius() * 2.0f / maxVelocity;
	return std::min(dt, maxTimeStep / 2.0f);
}

float DFSPHSolver::calculateAverageDensity(const std::vector<DFSPHParticle*>& particles)
{
	//const auto particleCount = particles.size();
	float totalDensity = 0.0f;
	for (auto p : particles) {
		totalDensity += p->getPredictedDensity();
	}
	return totalDensity / (float)particles.size();
}

float DFSPHSolver::calculateAverageDpDt(const std::vector<DFSPHParticle*>& particles)
{
	float totalDensity = 0.0f;
	for (auto p : particles) {
		totalDensity += p->getDpDt();
	}
	return totalDensity / (float)particles.size();
}