#include "WireFrameMenu.h"

#include "CGLib/UI/Panel.h"
#include "Crystal/AppBase/MenuItem.h"

#include "WFLineView.h"
#include "WFSphereView.h"

using namespace Crystal::UI;

WireFrameMenu::WireFrameMenu(const std::string& name, Panel* control, WorldBase* world, RendererBase* renderer) :
	IMenu(name)
{
	add(new MenuItem("Line", [control, world, renderer]() {
		control->clear();
		control->add(new WFLineView("WFLine", world, renderer));
		}));
	add(new MenuItem("Sphere", [control, world, renderer]() {
		control->clear();
		control->add(new WFSphereView("WFSphere", world, renderer));
		}));
}
