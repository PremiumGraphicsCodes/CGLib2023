#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Ellipse3dView.h"
#include "CGLib/UI/IntView.h"

namespace Crystal {
	namespace UI {

class WorldBase;
class RendererBase;

class WFEllipseView : public IOkCancelView
{
public:
	WFEllipseView(const std::string& name, WorldBase* world, RendererBase* renderer);

	void onOk() override;

private:
	Ellipse3dView ellipseView;
	IntView uNumView;
	IntView vNumView;
	WorldBase* world;
	RendererBase* renderer;
};

	}
}