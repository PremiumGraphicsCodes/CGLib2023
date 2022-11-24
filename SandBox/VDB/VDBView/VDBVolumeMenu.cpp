#include "VDBVolumeMenu.h"

#include "CGLib/UI/Panel.h"
#include "CGLib/UI/MenuItem.h"

#include "VDBVolumeSphereView.h"

using namespace Crystal::UI;

VDBVolumeMenu::VDBVolumeMenu(const std::string& name, World* world, Renderer* renderer, Panel* control) :
	IMenu(name)
{
	add(new MenuItem("Box", [control, world, renderer]() {
		control->setChild(new VDBVolumeSphereView("Box", world));
		}));
}