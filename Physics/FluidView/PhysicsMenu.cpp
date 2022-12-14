#include "PhysicsMenu.h"

#include "CGLib/UI/Panel.h"
#include "CGLib/UI/MenuItem.h"
#include "CSPHFluidView.h"
#include "PBSPHFluidView.h"
#include "DFSPHFluidView.h"
#include "MVPFluidView.h"
#include "MVPFluidEmitterView.h"
#include "MVPSamplerView.h"
#include "SPHVolumeConverterView.h"
#include "DMBoundaryView.h"

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
	add(new MenuItem("DFSPH", [control, world, renderer]() {
		control->setChild(new DFSPHFluidView("DFSPHFluid", world, renderer));
		}));
	add(new MenuItem("MVP", [control, world, renderer]() {
		control->setChild(new MVPFluidView("MVPFluid", world, renderer));
		}));
	add(new MenuItem("MVPEmitter", [control, world, renderer]() {
		control->setChild(new MVPFluidEmitterView("MVPEmitter", world, renderer));
		}));
	add(new MenuItem("MVPSampler", [control, world, renderer]() {
		control->setChild(new MVPSamplerView("MVPSampler", world, renderer));
		}));
	add(new MenuItem("SPHVolume", [control, world, renderer]() {
		control->setChild(new SPHVolumeConverterView("SPHVolume", world, renderer));
		}));
	add(new MenuItem("DMBoundary", [control, world, renderer]() {
		control->setChild(new DMBoundaryView("DMBoundary", world, renderer));
		}));
}
