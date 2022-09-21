#include "SpaceMenu.h"

#include "CGLib/UI/Panel.h"
#include "Crystal/AppBase/MenuItem.h"
//#include "PSBoxView.h"

using namespace Crystal::UI;

SpaceMenu::SpaceMenu(const std::string& name, Panel* control, IWorld* world, RendererBase* renderer) :
	IMenu(name)
{
	add(new MenuItem("SpaceHash", [&control, &world, &renderer]() {
		//control->clear();
		//control->add(new PSBoxView("PSBox", world, renderer));
		}));
}
