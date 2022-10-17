#include "WFEllipseView.h"
#include "Renderer.h"
#include "World.h"
#include "Crystal/Scene/WireFrameScene.h"
#include "CGLib/Shape/WireFrameBuilder.h"

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

	auto scene = new WireFrameScene();
	WireFrameBuilder wfBuilder;
	wfBuilder.add(e, uNumView.getValue(), vNumView.getValue());
	scene->setShape(std::move(wfBuilder.toWireFrame()));

	auto wfPresenter = std::make_unique<Crystal::Scene::WireFramePresenter>(scene, renderer->getLineRenderer());
	wfPresenter->build();
	wfPresenter->send();
	scene->setPresenter(std::move(wfPresenter));

	world->getRootScene()->addScene(scene);
}