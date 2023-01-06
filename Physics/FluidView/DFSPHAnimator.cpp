#include "DFSPHAnimator.h"
#include "DFSPHFluidScene.h"

using namespace Crystal::Physics;

DFSPHAnimator::DFSPHAnimator() :
	timeStep(0.001)
{
	//solver = std::make_unique<CSPHSolver>();
}

void DFSPHAnimator::step()
{
	solver->simulate(timeStep, 2.25, 2.5, 3);
	for (auto p : scene->getPresenters()) {
		p->send();
	}
}
