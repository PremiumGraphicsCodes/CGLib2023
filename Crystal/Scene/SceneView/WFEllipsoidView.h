#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Ellipsoid3dView.h"
#include "CGLib/UI/IntView.h"

namespace Crystal {
	namespace UI {

class World;
class Renderer;

class WFEllipsoidView : public IOkCancelView
{
public:
	WFEllipsoidView(const std::string& name, World* world, Renderer* renderer);

	void onOk() override;

private:
	Ellipsoid3dView ellipsoidView;
	IntView uNumView;
	IntView vNumView;
	World* world;
	Renderer* renderer;
};

	}
}