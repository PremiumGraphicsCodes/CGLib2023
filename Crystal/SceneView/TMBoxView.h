#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Box3dView.h"

namespace Crystal {
	namespace UI {
		class World;
		class Renderer;

class TMBoxView : public IOkCancelView
{
public:
	explicit TMBoxView(const std::string& name, World* world, Renderer* renderer);

	void onOk() override;

private:
	Box3dView boxView;
	World* world;
	Renderer* renderer;
};

	}
}