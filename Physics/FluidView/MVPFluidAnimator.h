#pragma once

#include "Crystal/Scene/Scene/IAnimator.h"
#include "../Fluid/MVPFluidSolver.h"
#include <memory>

namespace Crystal {
	namespace Physics {
		class MVPFluidScene;

class MVPFluidAnimator : public Scene::IAnimator
{
public:
	MVPFluidAnimator();

	void setSolver(std::unique_ptr<MVPFluidSolver> solver) { this->solver = std::move(solver); }

	void setScene(MVPFluidScene* scene) { this->scene = scene; }

	void step() override;

	void setTimeStep(const float timeStep) { this->timeStep = timeStep; }

	MVPFluidSolver* getSolver() { return solver.get(); }

private:
	std::unique_ptr<MVPFluidSolver> solver;
	MVPFluidScene* scene;
	float timeStep;
};

	}
}