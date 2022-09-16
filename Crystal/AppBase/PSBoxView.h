#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Box3dView.h"
#include "CGLib/UI/IntView.h"

namespace Crystal {
	namespace UI {
		class IWorld;
		class IRenderer;

class PSBoxView : public IOkCancelView
{
public:
	explicit PSBoxView(const std::string& name, IWorld* world, IRenderer* renderer);

	void onOk() override;

private:
	Box3dView boxView;
	IntView countView;
	IWorld* world;
	IRenderer* renderer;
};

	}
}