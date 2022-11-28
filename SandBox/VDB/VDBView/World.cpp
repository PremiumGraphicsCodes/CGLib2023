#include "World.h"

#include "Renderer.h"

#include "VDBPointsScene.h"
#include "VDBPointsPresenter.h"
#include "VDBVolumeScene.h"
#include "VDBVolumePresenter.h"
#include "VDBMeshScene.h"
#include "VDBMeshPresenter.h"

using namespace Crystal::Scene;
using namespace Crystal::VDB;
using namespace Crystal::UI;

void World::add(std::unique_ptr<VDBPoints>&& points)
{
	auto scene = new VDBPointsScene();
	scene->setId(getNextId());
	scene->setShape(std::move(points));

	auto presenter = std::make_unique<VDBPointsPresenter>(scene, renderer->getPointRenderer());
	presenter->build();
	presenter->send();
	scene->addPresenter(presenter.get());
	getRootScene()->addScene(scene);

	this->presenters.push_back(std::move(presenter));
}

void World::add(std::unique_ptr<VDBVolume>&& volume)
{
	auto scene = new VDBVolumeScene();
	scene->setId(getNextId());
	scene->setShape(std::move(volume));

	auto presenter = std::make_unique<VDBVolumePresenter>(scene, renderer->getPointRenderer());
	presenter->build();
	presenter->send();
	scene->addPresenter(presenter.get());
	getRootScene()->addScene(scene);

	this->presenters.push_back(std::move(presenter));
}

void World::add(std::unique_ptr<VDBMesh>&& mesh)
{
	auto scene = new VDBMeshScene();
	scene->setId(getNextId());
	scene->setShape(std::move(mesh));

	auto presenter = std::make_unique<VDBMeshPresenter>(scene, renderer->getTriangleRenderer());
	presenter->build();
	presenter->send();
	scene->addPresenter(presenter.get());
	getRootScene()->addScene(scene);

	this->presenters.push_back(std::move(presenter));
}

std::list<IPresenter*> World::getPresenters()
{
	std::list<IPresenter*> actives;
	for (auto s : getRootScene()->getChildren()) {
		if (!s->isVisible()) {
			continue;
		}
		const auto ps = s->getPresenters();
		actives.insert(actives.end(), ps.begin(), ps.end());
	}
	return actives;
}
