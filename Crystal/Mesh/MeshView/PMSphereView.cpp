#include "PMSphereView.h"
#include "Renderer.h"
#include "World.h"

#include "../Mesh/PolygonMesh.h"
#include "../Mesh/PolygonMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Mesh;

PMSphereView::PMSphereView(const std::string& name, World* world, Renderer* renderer) :
	IOkCancelView(name),
	sphereView("Sphere"),
	unumView("UNum", 12),
	vnumVIew("VNum", 12),
	world(world),
	renderer(renderer)
{
	add(&sphereView);
	add(&unumView);
	add(&vnumVIew);
}

void PMSphereView::onOk()
{
	PolygonMeshBuilder builder;
	builder.add(sphereView.getValue(), unumView.getValue(), vnumVIew.getValue());
	world->add(builder.build());
}