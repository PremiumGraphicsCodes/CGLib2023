#include "PSBoxView.h"

#include "ParticleSystemScene.h"
#include "ParticleSystemBuilder.h"
#include "Renderer.h"
#include "World.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PSBoxView::PSBoxView(const std::string& name, World* world, Renderer* renderer) :
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

void PSBoxView::onOk()
{
	const auto box = boxView.getValue();

	auto scene = new ParticleSystemScene();
	ParticleSystemBuilder builder;
	builder.add(box, uNumView.getValue(), vNumView.getValue(), wNumView.getValue());
	scene->setShape(std::move(builder.toParticleSystem()));

	auto presenter = std::make_unique<Crystal::Scene::ParticleSystemPresenter>(scene, renderer->getPointRenderer());
	presenter->build();
	presenter->send();
	scene->setPresenter(std::move(presenter));
	world->getRootScene()->addScene(scene);
}