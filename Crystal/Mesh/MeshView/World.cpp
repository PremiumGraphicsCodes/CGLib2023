#include "World.h"

#include "Renderer.h"
#include "PolygonMeshScene.h"
#include "PolygonMeshPresenter.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Mesh;

void World::add(std::unique_ptr<PolygonMesh>&& points)
{
	auto scene = new PolygonMeshScene();
	scene->setId(getNextId());
	scene->setShape(std::move(points));

	auto presenter = std::make_unique<PolygonMeshPresenter>(scene, renderer->getTriangleRenderer());
	presenter->build();
	presenter->send();
	scene->addPresenter(presenter.get());
	getRootScene()->addScene(scene);

	this->presenters.push_back(std::move(presenter));
}

/*
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
*/

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
