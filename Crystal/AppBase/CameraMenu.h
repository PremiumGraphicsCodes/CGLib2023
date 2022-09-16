#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {

class CameraMenu : public IMenu
{
public:
	CameraMenu(const std::string& name);

private:
	void onFit();

	void onXY();

	void onYZ();

	void onZX();
};

	}
}