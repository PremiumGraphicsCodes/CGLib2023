#include "WFCylinderView.h"
#include "Crystal/AppBase/RendererBase.h"
#include "Crystal/AppBase/WorldBase.h"
#include "Crystal/Scene/WireFrameScene.h"
#include "CGLib/Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFCylinderView::WFCylinderView(const std::string& name, WorldBase* world, RendererBase* renderer) :
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