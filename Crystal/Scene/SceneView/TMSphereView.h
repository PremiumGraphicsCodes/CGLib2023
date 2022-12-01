#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Sphere3dView.h"
#include "CGLib/UI/IntView.h"

namespace Crystal {
	namespace UI {
		class World;
		class Renderer;

class TMSphereView : public IOkCancelView
{
public:
	TMSphereView(const std::string& name, World* world, Renderer* renderer);

	void onOk() override;

private:
	Sphere3dView sphereView;
	IntView unumView;
	IntView vnumView;
	World* world;
	Renderer* renderer;
};

	}
}