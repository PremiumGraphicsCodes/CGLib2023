#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Ellipse3dView.h"
#include "CGLib/UI/IntView.h"

namespace Crystal {
	namespace UI {

class World;
class Renderer;

class WFEllipseView : public IOkCancelView
{
public:
	WFEllipseView(const std::string& name, World* world, Renderer* renderer);

	void onOk() override;

private:
	Ellipse3dView ellipseView;
	IntView uNumView;
	IntView vNumView;
	World* world;
	Renderer* renderer;
};

	}
}