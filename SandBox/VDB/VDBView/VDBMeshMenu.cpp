#include "VDBMeshMenu.h"

#include "CGLib/UI/Panel.h"
#include "CGLib/UI/MenuItem.h"

#include "VDBMeshBoxView.h"

using namespace Crystal::UI;

VDBMeshMenu::VDBMeshMenu(const std::string& name, World* world, Renderer* renderer, Panel* control) :
	IMenu(name)
{
	add(new MenuItem("Box", [control, world, renderer]() {
		control->setChild(new VDBMeshBoxView("Box", world, renderer));
		}));
}