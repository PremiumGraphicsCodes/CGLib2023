#pragma once

#include "CGLib/UI/IMenu.h"

namespace Crystal {
	namespace UI {
		class Canvas;
		class Renderer;

class CtrlMenu : public IMenu
{
public:
	CtrlMenu(const std::string& name, Canvas* canvas, Renderer* renderer);

private:
};

	}
}