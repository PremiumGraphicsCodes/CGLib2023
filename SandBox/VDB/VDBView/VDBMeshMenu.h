#pragma once

#include "CGLib/UI/IMenu.h"
#include "World.h"
#include "Renderer.h"

namespace Crystal {
	namespace UI {
		class Panel;

class VDBMeshMenu : public IMenu
{
public:
	VDBMeshMenu(const std::string& name, World* world, Renderer* renderer, Panel* control);
};

	}
}