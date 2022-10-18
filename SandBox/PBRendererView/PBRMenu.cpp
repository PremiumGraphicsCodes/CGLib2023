#include "PBRMenu.h"

#include "CGLib/UI/Panel.h"
#include "Crystal/AppBase/MenuItem.h"

using namespace Crystal::UI;

PBRMenu::PBRMenu(const std::string& name, World* world, Renderer* renderer) :
	IMenu(name)
{
	add(new MenuItem("DFLight", [world, renderer]() {
		}));
	add(new MenuItem("IBL", [world, renderer]() {
		}));
	add(new MenuItem("PBLight", [&world, &renderer]() {
		}));
}
