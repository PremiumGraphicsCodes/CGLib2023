#include "TMCylinderView.h"
#include "Renderer.h"
#include "World.h"
#include "TriangleMeshScene.h"
#include "TriangleMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

TMCylinderView::TMCylinderView(const std::string& name, World* world, Renderer* renderer) :
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

void TMCylinderView::onOk()
{
	const auto e = cylinderView.getValue();

	auto scene = new TriangleMeshScene();
	TriangleMeshBuilder builder;
	builder.add(e, uNumView.getValue(), vNumView.getValue());
	scene->setShape(std::move(builder.build()));

	auto wfPresenter = std::make_unique<TriangleMeshPresenter>(scene, renderer->getTriangleRenderer());
	wfPresenter->build();
	wfPresenter->send();
	scene->setPresenter(std::move(wfPresenter));

	world->getRootScene()->addScene(scene);
}