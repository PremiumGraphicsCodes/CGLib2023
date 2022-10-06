#include "CSPHAnimator.h"
#include "CSPHFluidScene.h"

using namespace Crystal::Physics;

CSPHAnimator::CSPHAnimator()
{
	//solver = std::make_unique<CSPHSolver>();
}

void CSPHAnimator::step()
{
	solver->simulate();
	scene->getPresenter()->send();
}
