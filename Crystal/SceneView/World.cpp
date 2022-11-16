#include "World.h"

#include <memory>
#include "ParticleSystemPresenter.h"

#include "ParticleSystemScene.h"
#include "WireFrameScene.h"

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

void World::addWireFrame(std::unique_ptr<WireFrame>&& wireFrame)
{
	auto scene = new WireFrameScene();
	scene->setShape(std::move(wireFrame));
	auto wfPresenter = std::make_unique<Crystal::Scene::WireFramePresenter>(scene, renderer->getLineRenderer());
	wfPresenter->build();
	wfPresenter->send();
	scene->setPresenter(std::move(wfPresenter));
	getRootScene()->addScene(scene);
}