#include "ShapeMenu.h"

#include "ParticleSystemMenu.h"
#include "WireFrameMenu.h"

using namespace Crystal::UI;

ShapeMenu::ShapeMenu(const std::string& name, WorldBase* world, RendererBase* renderer, Panel* control) :
	IMenu(name)
{
	add(new ParticleSystemMenu("ParticleSystem", control, world, renderer));
	add(new WireFrameMenu("WireFrame", control, world, renderer));
}
