#include "WireFrameMenu.h"

#include "CGLib/UI/Panel.h"
#include "Crystal/AppBase/MenuItem.h"
#include "PSBoxView.h"

using namespace Crystal::UI;

WireFrameMenu::WireFrameMenu(const std::string& name, Panel* control, World* world, Renderer* renderer) :
	IMenu(name)
{
	/*
	add(new MenuItem("Sphere", [&control, &world, &renderer]() {
		control->add(new PSBoxView("PSBox", world, renderer));
		}));
		*/
}
