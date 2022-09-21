#pragma once

#include "Crystal/AppBase/IMenu.h"

namespace Crystal {
	namespace UI {
		class Panel;
		class WorldBase;
		class RendererBase;

class ParticleSystemMenu : public IMenu
{
public:
	ParticleSystemMenu(const std::string& name, Panel* control, WorldBase* world, RendererBase* renderer);

};

	}
}