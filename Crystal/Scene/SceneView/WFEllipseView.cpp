#include "WFEllipseView.h"
#include "Renderer.h"
#include "World.h"
#include "WireFrameScene.h"
#include "WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFEllipseView::WFEllipseView(const std::string& name, World* world, Renderer* renderer) :
	IOkCancelView(name),
	ellipseView("Ellipse"),
	uNumView("UNum", 12),
	vNumView("VNum", 12),
	world(world),
	renderer(renderer)
{
	add(&ellipseView);
	add(&uNumView);
	add(&vNumView);
}

void WFEllipseView::onOk()
{
	const auto e = ellipseView.getValue();

	WireFrameBuilder wfBuilder;
	wfBuilder.add(e, uNumView.getValue(), vNumView.getValue());
	world->addWireFrame( wfBuilder.toWireFrame());
}