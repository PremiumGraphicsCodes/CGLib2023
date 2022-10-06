#include "CSPHAnimator.h"

using namespace Crystal::Physics;

CSPHAnimator::CSPHAnimator() :
	timeStep(0.001)
{
	//solver = std::make_unique<CSPHSolver>();
}

void CSPHAnimator::step()
{
	solver->simulate(timeStep);
}
