#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/FloatView.h"
#include "CGLib/UI/Sphere3dView.h"

namespace Crystal {
	namespace UI {
		class World;
		class Renderer;

class SignedDistanceCalculatorView : public IOkCancelView
{
public:
	SignedDistanceCalculatorView(const std::string& name, World* world, Renderer* renderer);

	void onOk() override;

private:
	Sphere3dView sphereView;
	World* world;
	Renderer* renderer;
};

	}
}