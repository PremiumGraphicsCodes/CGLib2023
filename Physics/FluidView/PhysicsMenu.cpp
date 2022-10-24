#include "PhysicsMenu.h"

#include "CGLib/UI/Panel.h"
#include "Crystal/AppBase/MenuItem.h"
#include "CSPHFluidView.h"
#include "PBSPHFluidView.h"
#include "MVPFluidView.h"
#include "MVPSamplerView.h"

using namespace Crystal::UI;

PhysicsMenu::PhysicsMenu(const std::string& name, World* world, Renderer* renderer, Panel* control) :
	IMenu(name)
{
	add(new MenuItem("CSPH", [control, world, renderer]() {
		control->setChild(new CSPHFluidView("CSPHFluid", world, renderer));
		}));
	add(new MenuItem("PBSPH", [control, world, renderer]() {
		control->setChild(new PBSPHFluidView("PBSPHFluid", world, renderer));
		}));
	add(new MenuItem("MVP", [control, world, renderer]() {
		control->setChild(new MVPFluidView("MVPFluid", world, renderer));
		}));
	add(new MenuItem("MVPSampler", [control, world, renderer]() {
		control->setChild(new MVPSamplerView("MVPSampler", world, renderer));
		}));
}
