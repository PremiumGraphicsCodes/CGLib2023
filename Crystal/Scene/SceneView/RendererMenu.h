#pragma once

#include "CGLib/UI//IMenu.h"

namespace Crystal {
	namespace UI {
		class World;
		class Renderer;
		class Panel;

class RendererMenu : public IMenu
{
public:
	RendererMenu(const std::string& name, World* world, Renderer* renderer);

private:
};

	}
}