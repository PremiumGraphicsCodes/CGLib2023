#pragma once

#include "Crystal/AppBase/IMenu.h"

namespace Crystal {
	namespace UI {
		class Panel;
		class World;
		class Renderer;

class ParticleSystemMenu : public IMenu
{
public:
	ParticleSystemMenu(const std::string& name, Panel* control, World* world, Renderer* renderer);

};

	}
}