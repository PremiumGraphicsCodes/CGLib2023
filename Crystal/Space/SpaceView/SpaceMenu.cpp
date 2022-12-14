#include "SpaceMenu.h"

#include "CGLib/UI/Panel.h"
#include "CGLib/UI/MenuItem.h"

#include "SpaceHashView.h"
#include "CompactSpaceHashView.h"
#include "SignedDistanceCalculatorView.h"
//#include "PSBoxView.h"

using namespace Crystal::UI;

SpaceMenu::SpaceMenu(const std::string& name, Panel* control, World* world, Renderer* renderer) :
	IMenu(name)
{
	add(new MenuItem("SpaceHash", [&control, &world, &renderer]() {
		control->setChild(new SpaceHashView("SpaceHash", world, renderer));
		}));
	add(new MenuItem("CompactSpaceHash", [control, world, renderer]() {
		control->setChild(new CompactSpaceHashView("CompactSpaceHash", world, renderer));
		}));
	add(new MenuItem("SignedDistance", [control, world, renderer]() {
		control->setChild(new SignedDistanceCalculatorView("SignedDistance", world, renderer));
		}));
}
