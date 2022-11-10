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

	auto scene = new PointCloudScene();
	PointCloudBuilder builder;
	builder.add(box, uNumView.getValue(), vNumView.getValue(), wNumView.getValue());
	const auto pc = builder.toPointCloud();
	const auto& points = pc->getPoints();
	for (auto& p : points) {
		p->setColor(ColorRGBAf(0, 0, 1, 0));
	}
	scene->setShape(std::move(builder.toPointCloud()));

	auto presenter = std::make_unique<PointCloudPresenter>(scene, renderer->getPointRenderer());
	presenter->build();
	presenter->send();
	scene->setPresenter(std::move(presenter));
	world->getRootScene()->addScene(scene);
}