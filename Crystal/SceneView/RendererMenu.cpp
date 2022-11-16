#include "RendererMenu.h"
#include "CGLib/UI/MenuItem.h"

#include "World.h"
#include "Renderer.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

RendererMenu::RendererMenu(const std::string& name, World* world, Renderer* renderer) :
	IMenu(name)
{
	add(new MenuItem("Main", [&renderer] { renderer->setTarget(Renderer::Target::Main); }));
	add(new MenuItem("Id", [&renderer] { renderer->setTarget(Renderer::Target::Id); }));
}