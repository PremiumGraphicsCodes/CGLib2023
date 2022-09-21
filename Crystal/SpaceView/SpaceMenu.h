#pragma once

#include "Crystal/AppBase/IMenu.h"

namespace Crystal {
	namespace UI {
		class Panel;
		class IWorld;
		class RendererBase;

class SpaceMenu : public IMenu
{
public:
	SpaceMenu(const std::string& name, Panel* control, IWorld* world, RendererBase* renderer);

};

	}
}