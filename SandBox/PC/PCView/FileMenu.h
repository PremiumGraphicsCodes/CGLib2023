#pragma once

#include "Crystal/AppBase/IMenu.h"
#include "World.h"
#include "Renderer.h"

namespace Crystal {
	namespace UI {

class FileMenu : public IMenu
{
public:
	FileMenu(const std::string& name, World* model, Renderer* renderer);

private:
	void onNew();

	void onImport();

	void onExport();

	World* world;
	Renderer* renderer;
};

	}
}