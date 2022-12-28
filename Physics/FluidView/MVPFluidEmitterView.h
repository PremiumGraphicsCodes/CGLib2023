#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Box3dView.h"
#include "CGLib/UI/FloatView.h"
#include "CGLib/UI/Vector3dView.h"
#include "CGLib/UI/IntView.h"

#include "../Fluid/MVPFluidEmitter.h"

#include "MVPFluidAnimator.h"

namespace Crystal {
	namespace Physics {
		class MVPFluidEmitterScene;
	}
	namespace UI {
		class World;
		class Renderer;

class MVPFluidEmitterView : public IView
{
public:
	MVPFluidEmitterView(const std::string& name, World* model, Renderer* renderer);

private:
	void onStart();

	void onReset();

	void onApply();

private:
	Physics::MVPFluidScene* fluidScene;
	Physics::MVPFluidSolver solver;
	Physics::MVPFluidAnimator* animator;
	FloatView pressureCoeView;
	FloatView viscosityCoeView;
	FloatView timeStepView;
	FloatView radiusView;
	Box3dView boundaryView;
	IntView intervalView;
	IntView startStepView;
	IntView endStepView;

	Vector3dView externalForceView;
	Button startButton;
	Button resetButton;
	Button applyButton;

	World* world;
	Renderer* renderer;
};

	}
}