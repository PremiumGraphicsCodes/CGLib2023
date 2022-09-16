#pragma once

#include "Crystal/AppBase/IMenu.h"

namespace Crystal {
	namespace UI {
		class Panel;
		class IWorld;
		class RendererBase;

class WireFrameMenu : public IMenu
{
public:
	WireFrameMenu(const std::string& name, Panel* control, IWorld* world, RendererBase* renderer);

};

	}
}