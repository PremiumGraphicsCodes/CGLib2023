#pragma once

#include "CGLib/UI//IMenu.h"

namespace Crystal {
	namespace UI {
		class World;
		class Renderer;
		class Panel;

class ShapeMenu : public IMenu
{
public:
	ShapeMenu(const std::string& name, World* world, Renderer* renderer, Panel* control);
};

	}
}