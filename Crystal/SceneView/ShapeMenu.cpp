#include "ShapeMenu.h"

#include "ParticleSystemMenu.h"
#include "WireFrameMenu.h"
#include "TriangleMeshMenu.h"

using namespace Crystal::UI;

ShapeMenu::ShapeMenu(const std::string& name, World* world, Renderer* renderer, Panel* control) :
	IMenu(name)
{
	add(new ParticleSystemMenu("ParticleSystem", control, world, renderer));
	add(new WireFrameMenu("WireFrame", control, world, renderer));
	add(new TriangleMeshMenu("TriangleMesh", control, world, renderer));
}
