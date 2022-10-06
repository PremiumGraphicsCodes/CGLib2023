#pragma once

#include "Crystal/AppBase/IMenu.h"

namespace Crystal {
	namespace UI {
		class WorldBase;
		class RendererBase;
		class Panel;

class PhysicsMenu : public IMenu
{
public:
	PhysicsMenu(const std::string& name, WorldBase* world, RendererBase* renderer, Panel* control);
};

	}
}