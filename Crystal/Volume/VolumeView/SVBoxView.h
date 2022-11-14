#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Box3dView.h"
#include "CGLib/UI/FloatView.h"

namespace Crystal {
	namespace UI {
		class World;
		class Renderer;

class SVBoxView : public IOkCancelView
{
public:
	SVBoxView(const std::string& name, World* world, Renderer* canvas);

	void onOk() override;

private:
	Box3dView boxView;
	FloatView cellLengthView;
	World* world;
	Renderer* renderer;
};

	}
}