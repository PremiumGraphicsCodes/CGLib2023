#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Cylinder3dView.h"
#include "CGLib/UI/IntView.h"

namespace Crystal {
	namespace UI {

class World;
class Renderer;

class TMCylinderView : public IOkCancelView
{
public:
	TMCylinderView(const std::string& name, World* world, Renderer* renderer);

	void onOk() override;

private:
	Cylinder3dView cylinderView;
	IntView uNumView;
	IntView vNumView;
	World* world;
	Renderer* renderer;
};

	}
}