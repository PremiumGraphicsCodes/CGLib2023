#include "WFLineView.h"

#include "WireFrameScene.h"
#include "Renderer.h"
#include "World.h"

//#include <random>

using namespace Crystal::Math;
using namespace Crystal::Shape;
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

	auto shape = std::make_unique<WireFrame>();
	shape->add(std::make_unique<Vertex>(Vector3df(0, 0, 0)));
	shape->add(std::make_unique<Vertex>(Vector3df(1, 0, 0)));
	shape->addEdge(WireFrame::Edge(0, 1));

	world->addWireFrame(std::move(shape));
}