#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Box3dView.h"
#include "CGLib/UI/IntView.h"

namespace Crystal {
	namespace UI {

class WorldBase;
class RendererBase;

class WFBoxView : public IOkCancelView
{
public:
	WFBoxView(const std::string& name, WorldBase* world, RendererBase* renderer);

	void onOk() override;

private:
	Box3dView boxView;
	IntView uNumView;
	IntView vNumView;
	IntView wNumView;
	WorldBase* world;
	RendererBase* renderer;
};

	}
}