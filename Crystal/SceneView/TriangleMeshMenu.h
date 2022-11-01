#pragma once

#include "Crystal/AppBase/IMenu.h"

namespace Crystal {
	namespace UI {
		class Panel;
		class World;
		class Renderer;

class TriangleMeshMenu : public IMenu
{
public:
	TriangleMeshMenu(const std::string& name, Panel* control, World* world, Renderer* renderer);
};

	}
}