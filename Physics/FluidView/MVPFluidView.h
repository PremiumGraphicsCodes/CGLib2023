#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Box3dView.h"
#include "CGLib/UI/FloatView.h"
#include "CGLib/UI/Vector3dView.h"

#include "Crystal/AppBase/SceneSelectView.h"

#include "../Fluid/MVPFluidSolver.h"

namespace Crystal {
	namespace Physics {
		class MVPFluidScene;
	}
	namespace UI {
		class World;
		class Renderer;

class MVPFluidView : public IView
{
public:
	MVPFluidView(const std::string& name, World* model, Renderer* renderer);

private:
	void onStart();

	void onReset();

private:
	Physics::MVPFluidScene* fluidScene;
	Physics::MVPFluidScene* staticScene;
	Physics::MVPFluidSolver solver;
	//Physics::MVPUpdater updator;
	FloatView pressureCoeView;
	FloatView viscosityCoeView;
	FloatView timeStepView;
	FloatView radiusView;
	Box3dView boundaryView;
	Vector3dView externalForceView;
	Button startButton;
	Button resetButton;
	int newId;

	World* world;
	Renderer* renderer;
};

	}
}