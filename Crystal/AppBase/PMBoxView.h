#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Box3dView.h"

namespace Crystal {
	namespace UI {
		class IWorld;
		class RendererBase;

class PMBoxView : public IOkCancelView
{
public:
	explicit PMBoxView(const std::string& name, IWorld* world, RendererBase* renderer);

	void onOk() override;

private:
	Box3dView boxView;
	IWorld* world;
	RendererBase* renderer;
};

	}
}