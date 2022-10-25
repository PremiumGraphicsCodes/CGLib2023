#pragma once

#include "Crystal/AppBase/IMenu.h"

namespace Crystal {
	namespace UI {
		class World;
		class Renderer;

class PBRMenu : public IMenu
{
public:
	PBRMenu(const std::string& name, World* world, Renderer* renderer);

};

	}
}