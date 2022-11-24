#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Sphere3dView.h"
#include "CGLib/UI/FloatView.h"

namespace Crystal {
	namespace Physics {
		class KFFluidScene;
	}
	namespace UI {
		class World;
		class Renderer;

class VDBPointsBoxView : public IOkCancelView
{
public:
	VDBPointsBoxView(const std::string& name, World* model, Renderer* canvas);

private:
	void onOk() override;

private:
	Sphere3dView sphereView;
	FloatView divideLengthView;
};

	}
}