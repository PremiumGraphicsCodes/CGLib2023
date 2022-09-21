#include "ParticleSystemMenu.h"

#include "CGLib/UI/Panel.h"
#include "Crystal/AppBase/MenuItem.h"
#include "PSBoxView.h"

using namespace Crystal::UI;

ParticleSystemMenu::ParticleSystemMenu(const std::string& name, Panel* control, WorldBase* world, RendererBase* renderer) :
	IMenu(name)
{
	add(new MenuItem("Sphere", [control, world, renderer]() {
		control->clear();
		control->add(new PSBoxView("PSBox", world, renderer));
		}));
}
