#include "VDBPointsMenu.h"

#include "CGLib/UI/Panel.h"
#include "CGLib/UI/MenuItem.h"

#include "VDBPointsBoxView.h"

using namespace Crystal::UI;

VDBPointsMenu::VDBPointsMenu(const std::string& name, World* world, Renderer* renderer, Panel* control) :
	IMenu(name)
{
	add(new MenuItem("Box", [control, world, renderer]() {
		control->setChild(new VDBPointsBoxView("Box", world, renderer));
		}));

}