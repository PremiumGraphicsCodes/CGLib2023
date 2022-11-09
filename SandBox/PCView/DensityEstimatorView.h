#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Box3dView.h"
#include "CGLib/UI/FloatView.h"
#include "Crystal/AppBase/SceneSelectView.h"

namespace Crystal {
	namespace UI {
		class World;
		class Renderer;

class DensityEstimatorView : public IOkCancelView
{
public:
	DensityEstimatorView(const std::string& name, World* world, Renderer* renderer);

	void onOk() override;

private:
	FloatView searchRadiusView;
	SceneSelectView pcSelectView;
	World* world;
	Renderer* renderer;
};

	}
}