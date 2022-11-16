#include "World.h"

#include <memory>
#include "ParticleSystemPresenter.h"

#include "ParticleSystemScene.h"

#include "Renderer.h"

using namespace Crystal::Shape;
using namespace Crystal::UI;
using namespace Crystal::Scene;

void World::addParticleSystem(std::unique_ptr<ParticleSystem>&& particleSystem)
{
	auto scene = new ParticleSystemScene();
	scene->setShape(std::move(particleSystem));
	auto presenter = std::make_unique<Crystal::Scene::ParticleSystemPresenter>(scene, renderer->getPointRenderer());
	presenter->build();
	presenter->send();
	scene->setPresenter(std::move(presenter));
	getRootScene()->addScene(scene);
}