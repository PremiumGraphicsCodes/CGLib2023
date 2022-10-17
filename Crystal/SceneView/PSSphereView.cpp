#include "PSSphereView.h"

#include "Crystal/Scene/ParticleSystemScene.h"
#include "Renderer.h"
#include "World.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PSSphereView::PSSphereView(const std::string& name, World* world, Renderer* renderer) :
	IOkCancelView(name),
	sphereView("Box"),
	countView("Count", 10000),
	world(world),
	renderer(renderer)
{
	add(&sphereView);
	add(&countView);
}

void PSSphereView::onOk()
{
	const auto sphere = sphereView.getValue();

	auto scene = new ParticleSystemScene();
	scene->setId(world->getNextId());

	auto shape = std::make_unique<ParticleSystem>();

	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<float> dist(0.0, 1.0);
	for (int i = 0; i < countView.getValue(); ++i) {
		const auto u = dist(mt);
		const auto v = dist(mt);
		const auto w = dist(mt);
		const auto pos = sphere.getPosition(u, v, w);
		shape->add(std::make_unique<Particle>(pos));
	}
	scene->setShape(std::move(shape));

	auto presenter = std::make_unique<Crystal::Scene::ParticleSystemPresenter>(scene, renderer->getPointRenderer());
	presenter->build();
	presenter->send();
	scene->setPresenter(std::move(presenter));
	world->getRootScene()->addScene(scene);
}