#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Box3dView.h"
#include "CGLib/UI/FloatView.h"
#include "CGLib/UI/IntView.h"

namespace Crystal {
	namespace UI {
		class World;
		class Renderer;

class NormalEstimatorView : public IOkCancelView
{
public:
	NormalEstimatorView(const std::string& name, World* world, Renderer* renderer);

	void onOk() override;

private:
	FloatView searchRadiusView;
	IntView pcIdView;
	World* world;
	Renderer* renderer;
};

	}
}