#include "PMBoxView.h"
#include "Renderer.h"
#include "World.h"

#include "PolygonMeshScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Mesh;

PMBoxView::PMBoxView(const std::string& name, World* world, Renderer* renderer) :
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
}