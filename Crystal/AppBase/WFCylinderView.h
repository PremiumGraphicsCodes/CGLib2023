#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Cylinder3dView.h"
#include "CGLib/UI/IntView.h"

namespace Crystal {
	namespace UI {

class WorldBase;
class RendererBase;

class WFCylinderView : public IOkCancelView
{
public:
	WFCylinderView(const std::string& name, WorldBase* world, RendererBase* renderer);

	void onOk() override;

private:
	Cylinder3dView cylinderView;
	IntView uNumView;
	IntView vNumView;
	WorldBase* world;
	RendererBase* renderer;
};

	}
}