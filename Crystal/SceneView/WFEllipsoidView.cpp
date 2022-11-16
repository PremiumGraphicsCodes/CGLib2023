#include "WFEllipsoidView.h"
#include "Renderer.h"
#include "World.h"
#include "WireFrameScene.h"
#include "WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFEllipsoidView::WFEllipsoidView(const std::string& name, World* world, Renderer* renderer) :
	IOkCancelView(name),
	ellipsoidView("Ellipsoid"),
	uNumView("UNum", 12),
	vNumView("VNum", 12),
	world(world),
	renderer(renderer)
{
	add(&ellipsoidView);
	add(&uNumView);
	add(&vNumView);
}

void WFEllipsoidView::onOk()
{
	const auto e = ellipsoidView.getValue();

	WireFrameBuilder wfBuilder;
	wfBuilder.add(e, uNumView.getValue(), vNumView.getValue());
	world->addWireFrame(std::move(wfBuilder.toWireFrame()));
}