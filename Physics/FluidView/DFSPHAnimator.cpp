#include "DFSPHAnimator.h"
#include "DFSPHFluidScene.h"

using namespace Crystal::Physics;

DFSPHAnimator::DFSPHAnimator()
{
	//solver = std::make_unique<CSPHSolver>();
}

void DFSPHAnimator::step()
{
	solver->simulate(2.5, 3);
	for (auto p : scene->getPresenters()) {
		p->send();
	}
}
