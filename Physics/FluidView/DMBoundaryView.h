#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/FloatView.h"
#include "CGLib/UI/Box3dView.h"

namespace Crystal {
	namespace UI {
		class World;
		class Renderer;

class DMBoundaryView : public IOkCancelView
{
public:
	DMBoundaryView(const std::string& name, World* world, Renderer* renderer);

	void onOk() override;

private:
	Box3dView boxView;
	World* world;
	Renderer* renderer;
};

	}
}