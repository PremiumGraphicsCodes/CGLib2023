#include "MeshMenu.h"

#include "CGLib/UI/Panel.h"
#include "CGLib/UI/MenuItem.h"
#include "PMBoxView.h"
#include "PMSphereView.h"

using namespace Crystal::UI;

MeshMenu::MeshMenu(const std::string& name, World* world, Renderer* renderer, Panel* control) :
	IMenu(name)
{
	add(new MenuItem("Box", [control, world, renderer]() {
		control->setChild(new PMBoxView("PMBox", world, renderer));
		}));
	add(new MenuItem("Sphere", [control, world, renderer]() {
		control->setChild(new PMSphereView("PMSphere", world, renderer));
		}));
}
