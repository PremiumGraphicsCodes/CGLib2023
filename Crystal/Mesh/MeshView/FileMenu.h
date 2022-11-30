#pragma once

#include "CGLib/UI//IMenu.h"

namespace Crystal {
	namespace UI {
		class World;
		class Renderer;
		class Panel;

class FileMenu : public IMenu
{
public:
	FileMenu(const std::string& name, World* world, Renderer* renderer);

private:
	World* world;
	Renderer* renderer;

	void onNew();

	void onImport();

	void onExport();
};

	}
}