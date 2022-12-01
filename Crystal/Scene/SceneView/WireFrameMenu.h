#pragma once

#include "CGLib/UI/IMenu.h"

namespace Crystal {
	namespace UI {
		class Panel;
		class World;
		class Renderer;

class WireFrameMenu : public IMenu
{
public:
	WireFrameMenu(const std::string& name, Panel* control, World* world, Renderer* renderer);

};

	}
}