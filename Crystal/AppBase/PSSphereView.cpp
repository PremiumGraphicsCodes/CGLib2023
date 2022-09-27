#include "PSSphereView.h"

#include "Crystal/Scene/ParticleSystemScene.h"
#include "RendererBase.h"
#include "WorldBase.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PSSphereView::PSSphereView(const std::string& name, WorldBase* world, RendererBase* renderer) :
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

	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<float> dist(0.0, 1.0);
	for (int i = 0; i < countView.getValue(); ++i) {
		const auto u = dist(mt);
		const auto v = dist(mt);
		const auto w = dist(mt);
		const auto pos = sphere.getPosition(u, v, w);
		scene->add(new Particle(pos));
	}

	auto presenter = std::make_unique<Crystal::Scene::ParticleSystemPresenter>(scene, renderer->getPointRenderer());
	presenter->build();
	presenter->send();
	scene->setPresenter(std::move(presenter));
	world->getRootScene()->addScene(scene);
}