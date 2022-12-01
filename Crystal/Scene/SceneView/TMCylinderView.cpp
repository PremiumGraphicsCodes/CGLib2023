#include "TMCylinderView.h"
#include "Renderer.h"
#include "World.h"
#include "TriangleMeshScene.h"
#include "TriangleMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

TMCylinderView::TMCylinderView(const std::string& name, World* world, Renderer* renderer) :
	IOkCancelView(name),
	cylinderView("Cylinder"),
	uNumView("UNum", 12),
	vNumView("VNum", 12),
	world(world),
	renderer(renderer)
{
	add(&cylinderView);
	add(&uNumView);
	add(&vNumView);
}

void TMCylinderView::onOk()
{
	const auto e = cylinderView.getValue();

	TriangleMeshBuilder builder;
	builder.add(e, uNumView.getValue(), vNumView.getValue());
	world->addTriangleMesh(std::move(builder.build()));
}