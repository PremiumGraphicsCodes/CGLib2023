#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Sphere3dView.h"
#include "CGLib/UI/IntView.h"

namespace Crystal {
	namespace UI {
		class World;
		class Renderer;

class PSSphereView : public IOkCancelView
{
public:
	explicit PSSphereView(const std::string& name, World* world, Renderer* renderer);

	void onOk() override;

private:
	Sphere3dView sphereView;
	IntView countView;
	World* world;
	Renderer* renderer;
};

	}
}