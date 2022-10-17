#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Ellipsoid3dView.h"
#include "CGLib/UI/IntView.h"

namespace Crystal {
	namespace UI {

class WorldBase;
class RendererBase;

class WFEllipsoidView : public IOkCancelView
{
public:
	WFEllipsoidView(const std::string& name, WorldBase* world, RendererBase* renderer);

	void onOk() override;

private:
	Ellipsoid3dView ellipsoidView;
	IntView uNumView;
	IntView vNumView;
	WorldBase* world;
	RendererBase* renderer;
};

	}
}