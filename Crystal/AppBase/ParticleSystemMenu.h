#pragma once

#include "Crystal/AppBase/IMenu.h"

namespace Crystal {
	namespace UI {
		class Panel;
		class IWorld;
		class RendererBase;

class ParticleSystemMenu : public IMenu
{
public:
	ParticleSystemMenu(const std::string& name, Panel* control, IWorld* world, RendererBase* renderer);

};

	}
}