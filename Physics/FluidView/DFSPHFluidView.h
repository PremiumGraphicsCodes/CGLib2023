#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/FloatView.h"
#include "CGLib/UI/Box3dView.h"
#include "World.h"
#include "Renderer.h"
#include "DFSPHAnimator.h"

namespace Crystal {
	namespace Physics {
		class DFSPHFluidScene;
		class DFSPHSolver;
	}
	namespace UI {

class DFSPHFluidView : public IOkCancelView
{
public:
	DFSPHFluidView(const std::string& name, World* model, Renderer* renderer);

private:
	void onOk() override;

	void onReset();

private:
	Physics::DFSPHSolver* simulator;
	Physics::DFSPHFluidScene* fluidScene;
	Physics::DFSPHAnimator* animator;
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