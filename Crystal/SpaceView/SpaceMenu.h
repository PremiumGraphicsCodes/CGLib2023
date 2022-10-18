#pragma once

#include "Crystal/AppBase/IMenu.h"

namespace Crystal {
	namespace UI {
		class Panel;
		class World;
		class Renderer;

class SpaceMenu : public IMenu
{
public:
	SpaceMenu(const std::string& name, Panel* control, World* world, Renderer* renderer);

};

	}
}