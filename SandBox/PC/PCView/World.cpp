#include "World.h"

#include "Renderer.h"

using namespace Crystal::UI;
using namespace Crystal::PC;

void World::add(std::unique_ptr<PointCloud>&& pointCloud)
{
	auto scene = new PointCloudScene();
	scene->setId(getNextId());
	scene->setShape(std::move(pointCloud));

	auto presenter = std::make_unique<PointCloudPresenter>(scene, renderer->getPointRenderer());
	presenter->build();
	presenter->send();
	scene->addPresenter(presenter.get());
	getRootScene()->addScene(scene);

	this->presenters.push_back(std::move(presenter));
}
