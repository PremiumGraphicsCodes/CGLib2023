#include "PhysicsMenu.h"

#include "CGLib/UI/Panel.h"
#include "Crystal/AppBase/MenuItem.h"
#include "CSPHFluidView.h"

using namespace Crystal::UI;

PhysicsMenu::PhysicsMenu(const std::string& name, WorldBase* world, RendererBase* renderer, Panel* control) :
	IMenu(name)
{
	add(new MenuItem("CSPH", [control, world, renderer]() {
		control->setChild(new CSPHFluidView("CSPHFluid", world, renderer));
		}));
}
