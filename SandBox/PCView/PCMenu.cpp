#include "PCMenu.h"

#include "CGLib/UI/Panel.h"
#include "Crystal/AppBase/MenuItem.h"

using namespace Crystal::UI;

PCMenu::PCMenu(const std::string& name, World* world, Renderer* renderer, Panel* control) :
	IMenu(name)
{
	/*
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
	add(new MenuItem("SPHVolume", [control, world, renderer]() {
		control->setChild(new SPHVolumeConverterView("SPHVolume", world, renderer));
		}));
		*/
}