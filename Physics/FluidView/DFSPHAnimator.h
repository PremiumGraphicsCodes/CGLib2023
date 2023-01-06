#pragma once

#include "Crystal/Scene/Scene/IAnimator.h"
#include "../Fluid/DFSPHSolver.h"
#include <memory>

namespace Crystal {
	namespace Physics {
		class DFSPHFluidScene;

class DFSPHAnimator : public Scene::IAnimator
{
public:
	DFSPHAnimator();

	void setSolver(std::unique_ptr<DFSPHSolver>&& solver) { this->solver = std::move(solver); }

	void setScene(DFSPHFluidScene* scene) { this->scene = scene; }

	void step() override;

	void setTimeStep(const float timeStep) { this->solver->setTimeStep(timeStep); }

private:
	std::unique_ptr<DFSPHSolver> solver;
	DFSPHFluidScene* scene;
};

	}
}