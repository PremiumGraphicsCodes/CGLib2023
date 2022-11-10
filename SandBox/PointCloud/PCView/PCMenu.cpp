#include "PCMenu.h"

#include "CGLib/UI/Panel.h"
#include "Crystal/AppBase/MenuItem.h"

#include "DensityEstimatorView.h"
#include "PCBoxView.h"

using namespace Crystal::UI;

PCMenu::PCMenu(const std::string& name, World* world, Renderer* renderer, Panel* control) :
	IMenu(name)
{
	add(new MenuItem("Density", [control, world, renderer]() {
		control->setChild(new DensityEstimatorView("Density", world, renderer));
		}));
	add(new MenuItem("PCBox", [control, world, renderer]() {
		control->setChild(new PCBoxView("PCBox", world, renderer));
		}));
}