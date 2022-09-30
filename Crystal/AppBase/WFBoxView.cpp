#include "WFBoxView.h"
#include "Crystal/AppBase/RendererBase.h"
#include "Crystal/AppBase/WorldBase.h"
#include "Crystal/Scene/WireFrameScene.h"
#include "CGLib/Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFBoxView::WFBoxView(const std::string& name, WorldBase* world, RendererBase* renderer) :
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

	auto scene = new WireFrameScene();
	WireFrameBuilder wfBuilder;
	wfBuilder.add(box, uNumView.getValue(), vNumView.getValue(), wNumView.getValue());
	scene->setShape(std::move(wfBuilder.toWireFrame()));

	auto wfPresenter = std::make_unique<Crystal::Scene::WireFramePresenter>(scene, renderer->getLineRenderer());
	wfPresenter->build();
	wfPresenter->send();
	scene->setPresenter(std::move(wfPresenter));

	world->getRootScene()->addScene(scene);
}