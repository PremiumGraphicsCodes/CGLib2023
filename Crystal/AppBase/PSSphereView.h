#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Sphere3dView.h"
#include "CGLib/UI/IntView.h"

namespace Crystal {
	namespace UI {
		class WorldBase;
		class RendererBase;

class PSSphereView : public IOkCancelView
{
public:
	explicit PSSphereView(const std::string& name, WorldBase* world, RendererBase* renderer);

	void onOk() override;

private:
	Sphere3dView sphereView;
	IntView countView;
	WorldBase* world;
	RendererBase* renderer;
};

	}
}