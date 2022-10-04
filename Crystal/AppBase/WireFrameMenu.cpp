#include "WireFrameMenu.h"

#include "CGLib/UI/Panel.h"
#include "Crystal/AppBase/MenuItem.h"

#include "WFLineView.h"
#include "WFBoxView.h"
#include "WFSphereView.h"
#include "WFEllipseView.h"
#include "WFEllipsoidView.h"
#include "WFCylinderView.h"

using namespace Crystal::UI;

WireFrameMenu::WireFrameMenu(const std::string& name, Panel* control, WorldBase* world, RendererBase* renderer) :
	IMenu(name)
{
	add(new MenuItem("Line", [control, world, renderer]() {
		control->setChild(new WFLineView("WFLine", world, renderer));
		}));
	add(new MenuItem("Box", [control, world, renderer]() {
		control->setChild(new WFBoxView("WFBox", world, renderer));
		}));
	add(new MenuItem("Sphere", [control, world, renderer]() {
		control->setChild(new WFSphereView("WFSphere", world, renderer));
		}));
	add(new MenuItem("Ellipse", [control, world, renderer]() {
		control->setChild(new WFEllipseView("WFEllipse", world, renderer));
		}));
	add(new MenuItem("Ellipsoid", [control, world, renderer]() {
		control->setChild(new WFEllipsoidView("WFEllipsoid", world, renderer));
		}));
	add(new MenuItem("Cylinder", [control, world, renderer]() {
		control->setChild(new WFCylinderView("WFCylinder", world, renderer));
		}));
}