#include "PMBoxView.h"
#include "Crystal/Scene/PolygonMeshScene.h"
#include "RendererBase.h"
#include "WorldBase.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PMBoxView::PMBoxView(const std::string& name, WorldBase* world, RendererBase* renderer) :
	IOkCancelView(name),
	boxView("Box"),
	world(world),
	renderer(renderer)
{
	add(&boxView);
}

void PMBoxView::onOk()
{
	const auto box = boxView.getValue();

	auto scene = new PolygonMeshScene();

	/*
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	for (int i = 0; i < countView.getValue(); ++i) {
		const auto u = dist(mt);
		const auto v = dist(mt);
		const auto w = dist(mt);
		const auto pos = box.getPosition(u, v, w);
		scene->add(new Particle(pos));
	}
	*/

	auto presenter = std::make_unique<Crystal::Scene::PolygonMeshPresenter>(scene, renderer->getTriangleRenderer());
	presenter->build();
	presenter->send();
	scene->setPresenter(std::move(presenter));
	world->getRootScene()->addScene(scene);
}