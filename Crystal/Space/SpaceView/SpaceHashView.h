#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/FloatView.h"
#include "Crystal/AppBase/SceneSelectView.h"

namespace Crystal {
	namespace UI {
		class World;
		class Renderer;

class SpaceHashView : public IOkCancelView
{
public:
	explicit SpaceHashView(const std::string& name, World* world, Renderer* renderer);

	void onOk() override;

private:
	SceneSelectView psSelectView;
	FloatView searchRadiusView;
	World* world;
	Renderer* renderer;
};

	}
}