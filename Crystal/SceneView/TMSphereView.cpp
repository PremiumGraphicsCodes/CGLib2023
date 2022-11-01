#include "TMSphereView.h"

#include "Crystal/Scene/TriangleMeshScene.h"
#include "CGLib/Shape/TriangleMeshBuilder.h"
#include "Renderer.h"
#include "World.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

TMSphereView::TMSphereView(const std::string& name, World* world, Renderer* renderer) :
	IOkCancelView(name),
	sphereView("Box"),
	unumView("UNum", 24),
	vnumView("VNum" ,24),
	world(world),
	renderer(renderer)
{
	add(&sphereView);
	add(&unumView);
	add(&vnumView);
}

void TMSphereView::onOk()
{
	const auto sphere = sphereView.getValue();

	auto scene = new TriangleMeshScene();
	scene->setId(world->getNextId());

	TriangleMeshBuilder builder;
	builder.add(sphere, unumView.getValue(), vnumView.getValue());
	scene->setShape(std::move(builder.build()));

	auto presenter = std::make_unique<TriangleMeshPresenter>(scene, renderer->getTriangleRenderer());
	presenter->build();
	presenter->send();
	scene->setPresenter(std::move(presenter));
	world->getRootScene()->addScene(scene);
}