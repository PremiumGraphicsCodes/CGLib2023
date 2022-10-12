#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/FloatView.h"
#include "CGLib/UI/Box3dView.h"
#include "Crystal/AppBase/WorldBase.h"
#include "Crystal/AppBase/RendererBase.h"

namespace Crystal {
	namespace Physics {
		class PBSPHFluidScene;
		class PBSPHSolver;
	}
	namespace UI {

class PBSPHFluidSimulationView : public IOkCancelView
{
public:
	PBSPHFluidSimulationView(const std::string& name, WorldBase* model, RendererBase* renderer);

private:
	void onOk() override;

	void onReset();

private:
	Physics::PBSPHSolver* simulator;
	Physics::PBSPHFluidScene* fluidScene;
	//	Physics::PBFluidScene* boundaryScene;
	Button startButton;
	Button resetButton;
	FloatView timeStepView;
	FloatView radiusView;
	FloatView effectLengthView;
	FloatView densityView;
	FloatView stiffnessView;
	FloatView vicsocityView;
	Box3dView boundaryView;
};

	}
}