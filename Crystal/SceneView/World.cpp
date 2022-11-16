#include "World.h"

#include <memory>
#include "ParticleSystemPresenter.h"

#include "ParticleSystemScene.h"
#include "WireFrameScene.h"
#include "TriangleMeshScene.h"

#include "ParticleSystemIdPresenter.h"

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

	auto idPresenter = std::make_unique<Crystal::Scene::ParticleSystemIdPresenter>(scene, renderer->getPointRenderer());
	idPresenter->build();
	idPresenter->send();
	idPresenters.push_back(std::move(idPresenter));
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

void World::addTriangleMesh(std::unique_ptr<TriangleMesh>&& mesh)
{
	auto scene = new TriangleMeshScene();
	scene->setShape(std::move(mesh));
	auto presenter = std::make_unique<TriangleMeshPresenter>(scene, renderer->getTriangleRenderer());
	presenter->build();
	presenter->send();
	scene->setPresenter(std::move(presenter));
	getRootScene()->addScene(scene);
}