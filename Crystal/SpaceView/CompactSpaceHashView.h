#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/FloatView.h"
#include "Crystal/AppBase/SceneSelectView.h"

namespace Crystal {
	namespace UI {
		class WorldBase;
		class RendererBase;

class CompactSpaceHashView : public IOkCancelView
{
public:
	explicit CompactSpaceHashView(const std::string& name, WorldBase* world, RendererBase* renderer);

	void onOk() override;

private:
	SceneSelectView psSelectView;
	FloatView searchRadiusView;
	WorldBase* world;
	RendererBase* renderer;
};

	}
}