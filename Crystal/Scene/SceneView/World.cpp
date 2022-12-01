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
	auto presenter = std::make_unique<ParticleSystemPresenter>(scene, renderer->getPointRenderer());
	presenter->build();
	presenter->send();
	scene->addPresenter(presenter.get());
	presenters.push_back(std::move(presenter));

	auto idPresenter = std::make_unique<ParticleSystemIdPresenter>(scene, renderer->getPointRenderer());
	idPresenter->build();
	idPresenter->send();
	scene->addPresenter(idPresenter.get());
	idPresenters.push_back(std::move(idPresenter));

	getRootScene()->addScene(scene);
}

void World::addWireFrame(std::unique_ptr<WireFrame>&& wireFrame)
{
	auto scene = new WireFrameScene();
	scene->setShape(std::move(wireFrame));
	auto presenter = std::make_unique<Crystal::Scene::WireFramePresenter>(scene, renderer->getLineRenderer());
	presenter->build();
	presenter->send();
	scene->addPresenter(presenter.get());
	presenters.push_back(std::move(presenter));
	getRootScene()->addScene(scene);
}

void World::addTriangleMesh(std::unique_ptr<TriangleMesh>&& mesh)
{
	auto scene = new TriangleMeshScene();
	scene->setShape(std::move(mesh));
	auto presenter = std::make_unique<TriangleMeshPresenter>(scene, renderer->getTriangleRenderer());
	presenter->build();
	presenter->send();
	scene->addPresenter(presenter.get());
	presenters.push_back(std::move(presenter));
	getRootScene()->addScene(scene);
}