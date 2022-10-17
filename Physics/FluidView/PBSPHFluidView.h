#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/FloatView.h"
#include "CGLib/UI/Box3dView.h"
#include "World.h"
#include "Renderer.h"
#include "PBSPHAnimator.h"

namespace Crystal {
	namespace Physics {
		class PBSPHFluidScene;
		class PBSPHSolver;
	}
	namespace UI {

class PBSPHFluidView : public IOkCancelView
{
public:
	PBSPHFluidView(const std::string& name, World* model, Renderer* renderer);

private:
	void onOk() override;

	void onReset();

private:
	Physics::PBSPHSolver* simulator;
	Physics::PBSPHFluidScene* fluidScene;
	Physics::PBSPHAnimator* animator;
	Button startButton;
	Button resetButton;
	FloatView timeStepView;
	FloatView radiusView;
	FloatView effectLengthView;
	FloatView densityView;
	FloatView stiffnessView;
	FloatView vicsocityView;
	Box3dView boundaryView;
	World* model;
	Renderer* renderer;
};

	}
}