#include "PCBoxView.h"

#include "PointCloudScene.h"
#include "PointCloudBuilder.h"
#include "Renderer.h"
#include "World.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::PC;
using namespace Crystal::UI;

PCBoxView::PCBoxView(const std::string& name, World* world, Renderer* renderer) :
	IOkCancelView(name),
	boxView("Box"),
	uNumView("UNum", 10),
	vNumView("VNum", 10),
	wNumView("WNum", 10),
	world(world),
	renderer(renderer)
{
	add(&boxView);
	add(&uNumView);
	add(&vNumView);
	add(&wNumView);
}

void PCBoxView::onOk()
{
	const auto box = boxView.getValue();

	PointCloudBuilder builder;
	builder.add(box, uNumView.getValue(), vNumView.getValue(), wNumView.getValue());
	const auto pc = builder.toPointCloud();
	const auto& points = pc->getPoints();
	for (auto& p : points) {
		p->setColor(ColorRGBAf(0, 0, 1, 0));
	}
	world->add(builder.toPointCloud());
}