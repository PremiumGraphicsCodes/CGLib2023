#pragma once

#include "../Scene/IAnimator.h"
#include "../Physics/PBSPHSolver.h"
#include <memory>

namespace Crystal {
	namespace Physics {
		class PBSPHFluidScene;

class PBSPHAnimator : public Scene::IAnimator
{
public:
	PBSPHAnimator();

	void setSolver(std::unique_ptr<PBSPHSolver> solver) { this->solver = std::move(solver); }

	void setScene(PBSPHFluidScene* scene) { this->scene = scene; }

	void step() override;

	void setTimeStep(const float timeStep) { this->timeStep = timeStep; }

private:
	std::unique_ptr<PBSPHSolver> solver;
	PBSPHFluidScene* scene;
	float timeStep;
};

	}
}