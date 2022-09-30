#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Sphere3dView.h"
#include "CGLib/UI/IntView.h"

namespace Crystal {
	namespace UI {

class WorldBase;
class RendererBase;

class WFSphereView : public IOkCancelView
{
public:
	explicit WFSphereView(const std::string& name, WorldBase* world, RendererBase* renderer);

	void onOk() override;

private:
	Sphere3dView sphereView;
	IntView uNumView;
	IntView vNumView;
	WorldBase* world;
	RendererBase* renderer;
};

	}
}