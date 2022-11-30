#include "PMBoxView.h"
#include "Renderer.h"
#include "World.h"

#include "../Mesh/PolygonMesh.h"
#include "../Mesh/PolygonMeshBuilder.h"

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

	PolygonMeshBuilder builder;
	builder.add(box);
	world->add(builder.build());
}