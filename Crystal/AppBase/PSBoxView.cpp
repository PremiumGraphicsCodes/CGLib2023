#include "PSBoxView.h"

#include "Crystal/Scene/ParticleSystemScene.h"
#include "IRenderer.h"
#include "IWorld.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PSBoxView::PSBoxView(const std::string& name, IWorld* world, IRenderer* renderer) :
	IOkCancelView(name),
	boxView("Box"),
	countView("Count", 10000),
	world(world),
	renderer(renderer)
{
	add(&boxView);
	add(&countView);
}

void PSBoxView::onOk()
{
	const auto box = boxView.getValue();

	auto scene = new ParticleSystemScene();

	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	for (int i = 0; i < countView.getValue(); ++i) {
		const auto u = dist(mt);
		const auto v = dist(mt);
		const auto w = dist(mt);
		const auto pos = box.getPosition(u, v, w);
		scene->add(new Particle(pos));
	}

	auto presenter = std::make_unique<Crystal::Scene::ParticleSystemPresenter>(scene, &renderer->point);
	presenter->build();
	presenter->send();
	scene->setPresenter(std::move(presenter));
	world->add(scene);
}