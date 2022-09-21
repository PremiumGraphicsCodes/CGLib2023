#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {
		class WorldBase;
		class RendererBase;
		class Panel;

class ShapeMenu : public IMenu
{
public:
	ShapeMenu(const std::string& name, WorldBase* world, RendererBase* renderer, Panel* control);
};

	}
}