#include "TriangleMeshMenu.h"

#include "CGLib/UI/Panel.h"
#include "Crystal/AppBase/MenuItem.h"

#include "TMBoxView.h"
#include "TMSphereView.h"
#include "TMCylinderView.h"

using namespace Crystal::UI;

TriangleMeshMenu::TriangleMeshMenu(const std::string& name, Panel* control, World* world, Renderer* renderer) :
	IMenu(name)
{
	add(new MenuItem("Box", [control, world, renderer]() {
		control->setChild(new TMBoxView("Box", world, renderer));
		}));
	add(new MenuItem("Sphere", [control, world, renderer]() {
		control->setChild(new TMSphereView("Sphere", world, renderer));
		}));
	add(new MenuItem("Cylinder", [control, world, renderer]() {
		control->setChild(new TMCylinderView("TMCylinder", world, renderer));
		}));
	/*
	add(new MenuItem("Ellipse", [control, world, renderer]() {
		control->setChild(new WFEllipseView("WFEllipse", world, renderer));
		}));
	add(new MenuItem("Ellipsoid", [control, world, renderer]() {
		control->setChild(new WFEllipsoidView("WFEllipsoid", world, renderer));
		}));
		*/
}