#pragma once

#include "CGLib/UI//IMenu.h"

namespace Crystal {
	namespace UI {
		class World;
		class Renderer;
		class Panel;

class MeshMenu : public IMenu
{
public:
	MeshMenu(const std::string& name, World* world, Renderer* renderer, Panel* control);
};

	}
}