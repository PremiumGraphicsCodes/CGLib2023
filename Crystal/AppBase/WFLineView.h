#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Line3dView.h"
//#include "CGLib/UI/IntView.h"

namespace Crystal {
	namespace UI {
		class IWorld;
		class RendererBase;

class WFLineView : public IOkCancelView
{
public:
	explicit WFLineView(const std::string& name, IWorld* world, RendererBase* renderer);

	void onOk() override;

private:
	Line3dView lineView;
	//IntView countView;
	IWorld* world;
	RendererBase* renderer;
};

	}
}