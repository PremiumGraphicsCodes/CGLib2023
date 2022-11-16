#include "TMBoxView.h"
#include "TriangleMeshScene.h"
#include "TriangleMeshBuilder.h"
#include "Renderer.h"
#include "World.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

TMBoxView::TMBoxView(const std::string& name, World* world, Renderer* renderer) :
	IOkCancelView(name),
	boxView("Box"),
	world(world),
	renderer(renderer)
{
	add(&boxView);
}

void TMBoxView::onOk()
{
	const auto box = boxView.getValue();

	TriangleMeshBuilder builder;
	builder.add(box, 2, 2, 2);
	world->addTriangleMesh(builder.build());
}