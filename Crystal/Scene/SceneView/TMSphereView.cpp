#include "TMSphereView.h"

#include "TriangleMeshScene.h"
#include "TriangleMeshBuilder.h"
#include "Renderer.h"
#include "World.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

TMSphereView::TMSphereView(const std::string& name, World* world, Renderer* renderer) :
	IOkCancelView(name),
	sphereView("Box"),
	unumView("UNum", 24),
	vnumView("VNum" ,24),
	world(world),
	renderer(renderer)
{
	add(&sphereView);
	add(&unumView);
	add(&vnumView);
}

void TMSphereView::onOk()
{
	const auto sphere = sphereView.getValue();

	TriangleMeshBuilder builder;
	builder.add(sphere, unumView.getValue(), vnumView.getValue());
	world->addTriangleMesh(std::move(builder.build()));
}