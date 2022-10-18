#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {
		class WorldBase;

class CameraMenu : public IMenu
{
public:
	CameraMenu(const std::string& name, WorldBase* world);

private:
	void onFit();

	void onXY();

	void onYZ();

	void onZX();

	WorldBase* world;
};

	}
}