#include "WFCylinderView.h"
#include "Renderer.h"
#include "World.h"
#include "WireFrameScene.h"
#include "WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFCylinderView::WFCylinderView(const std::string& name, World* world, Renderer* renderer) :
	IOkCancelView(name),
	cylinderView("Cylinder"),
	uNumView("UNum", 12),
	vNumView("VNum", 12),
	world(world),
	renderer(renderer)
{
	add(&cylinderView);
	add(&uNumView);
	add(&vNumView);
}

void WFCylinderView::onOk()
{
	const auto e = cylinderView.getValue();

	WireFrameBuilder wfBuilder;
	wfBuilder.add(e, uNumView.getValue(), vNumView.getValue());
	world->addWireFrame( std::move(wfBuilder.toWireFrame()) );
}