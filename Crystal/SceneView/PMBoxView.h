#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Box3dView.h"

namespace Crystal {
	namespace UI {
		class WorldBase;
		class RendererBase;

class PMBoxView : public IOkCancelView
{
public:
	explicit PMBoxView(const std::string& name, WorldBase* world, RendererBase* renderer);

	void onOk() override;

private:
	Box3dView boxView;
	WorldBase* world;
	RendererBase* renderer;
};

	}
}