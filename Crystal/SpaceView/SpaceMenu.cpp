#include "SpaceMenu.h"

#include "CGLib/UI/Panel.h"
#include "Crystal/AppBase/MenuItem.h"

#include "SpaceHashView.h"
//#include "PSBoxView.h"

using namespace Crystal::UI;

SpaceMenu::SpaceMenu(const std::string& name, Panel* control, WorldBase* world, RendererBase* renderer) :
	IMenu(name)
{
	add(new MenuItem("SpaceHash", [&control, &world, &renderer]() {
		control->clear();
		control->add(new SpaceHashView("SpaceHash", world, renderer));
		}));
}
