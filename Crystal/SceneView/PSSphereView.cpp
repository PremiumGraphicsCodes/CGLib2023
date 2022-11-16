#include "PSSphereView.h"

#include "ParticleSystemScene.h"
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
	world->addParticleSystem(std::move(shape));
}