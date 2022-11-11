#include "PCMenu.h"

#include "CGLib/UI/Panel.h"
#include "Crystal/AppBase/MenuItem.h"

#include "PCBoxView.h"
#include "DensityEstimatorView.h"
#include "NormalEstimatorView.h"
#include "CurvatureEstimatorView.h"

using namespace Crystal::UI;

PCMenu::PCMenu(const std::string& name, World* world, Renderer* renderer, Panel* control) :
	IMenu(name)
{
	add(new MenuItem("PCBox", [control, world, renderer]() {
		control->setChild(new PCBoxView("PCBox", world, renderer));
		}));

	add(new MenuItem("Density", [control, world, renderer]() {
		control->setChild(new DensityEstimatorView("Density", world, renderer));
		}));

	add(new MenuItem("Normal", [control, world, renderer]() {
		control->setChild(new NormalEstimatorView("Normal", world, renderer));
		}));

	add(new MenuItem("Curvature", [control, world, renderer]() {
		control->setChild(new CurvatureEstimatorView("Curvature", world, renderer));
		}));
}