#include "PBSPHAnimator.h"
#include "PBSPHFluidScene.h"

using namespace Crystal::Physics;

PBSPHAnimator::PBSPHAnimator() :
	timeStep(0.001)
{
	//solver = std::make_unique<CSPHSolver>();
}

void PBSPHAnimator::step()
{
	solver->simulate(timeStep, 3);
	for (auto p : scene->getPresenters()) {
		p->send();
	}
}
