#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Line3dView.h"
//#include "CGLib/UI/IntView.h"

namespace Crystal {
	namespace UI {
		class WorldBase;
		class RendererBase;

class WFLineView : public IOkCancelView
{
public:
	explicit WFLineView(const std::string& name, WorldBase* world, RendererBase* renderer);

	void onOk() override;

private:
	Line3dView lineView;
	//IntView countView;
	WorldBase* world;
	RendererBase* renderer;
};

	}
}