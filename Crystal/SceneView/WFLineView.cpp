#include "WFLineView.h"

#include "Crystal/Scene/WireFrameScene.h"
#include "Renderer.h"

//#include <random>

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFLineView::WFLineView(const std::string& name, World* world, Renderer* renderer) :
	IOkCancelView(name),
	lineView("Line"),
	//countView("Count", 10000),
	world(world),
	renderer(renderer)
{
	add(&lineView);
	//add(&countView);
}

void WFLineView::onOk()
{
	const auto line = lineView.getValue();

	auto scene = new WireFrameScene();
	scene->add(new Vertex(Vector3df(0, 0, 0)));
	scene->add(new Vertex(Vector3df(1, 0, 0)));
	scene->addIndex(0);
	scene->addIndex(1);

	auto wfPresenter = std::make_unique<Crystal::Scene::WireFramePresenter>(scene, &renderer->line);
	wfPresenter->build();
	wfPresenter->send();
	scene->setPresenter(std::move(wfPresenter));

	world->add(scene);
}