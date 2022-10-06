#include "CSPHSolver.h"
#include "CSPHParticle.h"
#include "CSPHBoundarySolver.h"
#include "CSPHFluid.h"

#include "Crystal/Space/IndexedSortBasedSeacher.h"

using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Physics;

void CSPHSolver::simulate(const float timeStep)
{
	std::vector<CSPHParticle*> particles;

	for (auto fluid : fluids) {
		const auto ps = fluid->getParticles();
		particles.insert(particles.end(), ps.begin(), ps.end());
	}

	SPHKernel kernel(effectLength);
	for (auto p : particles) {
		p->setKernel(&kernel);
	}

	for (auto particle : particles) {
		particle->init();
	}

	IndexedSortBasedSearcher algo(effectLength);
	for (auto p : particles) {
		algo.add(p->getPosition());
	}
	algo.search();
	const auto& pairs = algo.getPairs();

#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(pairs.size()); ++i) {
		auto p1 = particles[ pairs[i].first ];
		auto p2 = particles[ pairs[i].second ];
		p1->addDensity(*p2);
		p2->addDensity(*p1);
	}

	for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
		particles[i]->addSelfDensity();
	}

#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(pairs.size()); ++i) {
		auto p1 = particles[ pairs[i].first ];
		auto p2 = particles[ pairs[i].second ];
		p1->solvePressureForce(*p2);
		p2->solvePressureForce(*p1);
		p1->solveViscosityForce(*p2);
		p2->solveViscosityForce(*p1);
	}

	for (auto p : particles) {
		p->addExternalForce(externalForce);
	}

	CSPHBoundarySolver boundarySolver(timeStep, boundary);
	boundarySolver.solve(particles);

	for (auto p : particles) {
		p->forwardTime(timeStep);
	}

	/*
	for (auto fluid : fluids) {
		fluid->getPresenter()->updateView();
	}
	*/
}