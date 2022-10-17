#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Line3dView.h"
//#include "CGLib/UI/IntView.h"

namespace Crystal {
	namespace UI {
		class World;
		class Renderer;

class WFLineView : public IOkCancelView
{
public:
	WFLineView(const std::string& name, World* world, Renderer* renderer);

	void onOk() override;

private:
	Line3dView lineView;
	//IntView countView;
	World* world;
	Renderer* renderer;
};

	}
}