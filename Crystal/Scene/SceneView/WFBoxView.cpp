#include "WFBoxView.h"
#include "Renderer.h"
#include "World.h"
#include "WireFrameScene.h"
#include "WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFBoxView::WFBoxView(const std::string& name, World* world, Renderer* renderer) :
	IOkCancelView(name),
	boxView("Box"),
	uNumView("UNum", 1),
	vNumView("VNum", 1),
	wNumView("WNum", 1),
	world(world),
	renderer(renderer)
{
	add(&boxView);
	add(&uNumView);
	add(&vNumView);
	add(&wNumView);
}

void WFBoxView::onOk()
{
	const auto box = boxView.getValue();

	WireFrameBuilder wfBuilder;
	wfBuilder.add(box, uNumView.getValue(), vNumView.getValue(), wNumView.getValue());
	world->addWireFrame( std::move(wfBuilder.toWireFrame()));
}