#include "ParticleSystemMenu.h"

#include "CGLib/UI/Panel.h"
#include "Crystal/AppBase/MenuItem.h"
#include "PSBoxView.h"
#include "PSSphereView.h"

using namespace Crystal::UI;

ParticleSystemMenu::ParticleSystemMenu(const std::string& name, Panel* control, World* world, Renderer* renderer) :
	IMenu(name)
{
	add(new MenuItem("Box", [control, world, renderer]() {
		control->setChild(new PSBoxView("PSBox", world, renderer));
		}));
	add(new MenuItem("Sphere", [control, world, renderer]() {
		control->setChild(new PSSphereView("PSSphere", world, renderer));
		}));
}
