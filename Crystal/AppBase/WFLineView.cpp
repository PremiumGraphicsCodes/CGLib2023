#include "WFLineView.h"

#include "Crystal/Scene/WireFrameScene.h"
#include "Crystal/AppBase/RendererBase.h"
#include "Crystal/AppBase/WorldBase.h"

//#include <random>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFLineView::WFLineView(const std::string& name, WorldBase* world, RendererBase* renderer) :
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
	auto shape = std::make_unique<WireFrame>();
	shape->add(new Vertex(Vector3df(0, 0, 0)));
	shape->add(new Vertex(Vector3df(1, 0, 0)));
	shape->addEdge(WireFrame::Edge(0, 1));
	scene->setShape(std::move(shape));

	auto wfPresenter = std::make_unique<Crystal::Scene::WireFramePresenter>(scene, renderer->getLineRenderer());
	wfPresenter->build();
	wfPresenter->send();
	scene->setPresenter(std::move(wfPresenter));

	world->getRootScene()->addScene(scene);
}