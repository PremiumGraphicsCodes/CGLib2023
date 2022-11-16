#include "MVPFluidAnimator.h"
#include "MVPFluidScene.h"

using namespace Crystal::Physics;

MVPFluidAnimator::MVPFluidAnimator() :
	timeStep(0.001)
{
	//solver = std::make_unique<CSPHSolver>();
}

void MVPFluidAnimator::step()
{
	solver->simulate();
	for (auto p : scene->getPresenters()) {
		p->send();
	}
}
