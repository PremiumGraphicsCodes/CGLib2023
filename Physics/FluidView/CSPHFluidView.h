#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/FloatView.h"
#include "CGLib/UI/Box3dView.h"

#include "Crystal/AppBase/SceneSelectView.h"
#include "CSPHFluidScene.h"
#include "CSPHAnimator.h"

namespace Crystal {
	namespace UI {
		class World;
		class Renderer;

class CSPHFluidView : public IOkCancelView
{
public:
	CSPHFluidView(const std::string& name, World* model, Renderer* renderer);

private:
	void onOk() override;

	void onReset();

private:
	Physics::CSPHFluidScene* fluidScene;
	Physics::CSPHAnimator* animator;
	Button startButton;
	Button resetButton;
	//Button nextButton;
	FloatView pressureCoeView;
	FloatView viscosityView;
	FloatView timeStepView;
	FloatView densityView;
	Box3dView boundaryView;
	World* world;
	Renderer* renderer;
};

	}
}