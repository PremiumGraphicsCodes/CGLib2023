#include "PBRMenu.h"

#include "Renderer.h"

#include "CGLib/UI/Panel.h"
#include "Crystal/AppBase/MenuItem.h"

using namespace Crystal::UI;

PBRMenu::PBRMenu(const std::string& name, World* world, Renderer* renderer) :
	IMenu(name)
{
	add(new MenuItem("DFPolygon", [world, renderer]() {
		renderer->setTarget(Renderer::Target::DFPolygon);
		}));
	add(new MenuItem("IBL", [world, renderer]() {
		renderer->setTarget(Renderer::Target::IBL);
		}));
	add(new MenuItem("PBLight", [&world, &renderer]() {
		renderer->setTarget(Renderer::Target::PBLight);
		}));
}
