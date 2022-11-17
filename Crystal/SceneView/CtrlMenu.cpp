#include "CtrlMenu.h"
#include "CGLib/UI/MenuItem.h"

#include "Crystal/AppBase/Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

CtrlMenu::CtrlMenu(const std::string& name, Canvas* canvas) :
	IMenu(name)
{
	add(new MenuItem("Camera", [&canvas]
		{
		}));
	add(new MenuItem("Pick", [&canvas]
		{
		}));
}