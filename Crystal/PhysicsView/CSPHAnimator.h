#pragma once

#include "../Scene/IAnimator.h"
#include "../Physics/CSPHSolver.h"
#include <memory>

namespace Crystal {
	namespace Physics {

class CSPHAnimator : public Scene::IAnimator
{
public:
	CSPHAnimator();

	void setSolver(std::unique_ptr<CSPHSolver> solver) { this->solver = std::move(solver); }

	void step() override;

private:
	std::unique_ptr<CSPHSolver> solver;
	float timeStep;
	//solver->add(fluidScene->getFluid());

};
	}
}