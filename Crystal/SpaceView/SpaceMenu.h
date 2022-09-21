#pragma once

#include "Crystal/AppBase/IMenu.h"

namespace Crystal {
	namespace UI {
		class Panel;
		class WorldBase;
		class RendererBase;

class SpaceMenu : public IMenu
{
public:
	SpaceMenu(const std::string& name, Panel* control, WorldBase* world, RendererBase* renderer);

};

	}
}