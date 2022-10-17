#pragma once

#include "Crystal/Scene/IAnimator.h"
#include "../Physics/CSPHSolver.h"
#include <memory>

namespace Crystal {
	namespace Physics {
		class CSPHFluidScene;

class CSPHAnimator : public Scene::IAnimator
{
public:
	CSPHAnimator();

	void setSolver(std::unique_ptr<CSPHSolver> solver) { this->solver = std::move(solver); }

	void setScene(CSPHFluidScene* scene) { this->scene = scene; }

	void step() override;

private:
	std::unique_ptr<CSPHSolver> solver;
	CSPHFluidScene* scene;
};

	}
}