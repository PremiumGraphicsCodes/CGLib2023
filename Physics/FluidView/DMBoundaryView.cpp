#include "DMBoundaryView.h"

#include "World.h"
#include "Renderer.h"
#include <iostream>

#include "BoundaryScene.h"
#include "BoundaryPresenter.h"
#include "Physics/Fluid/DMBoundary.h"
#include "Physics/Fluid/SPHKernel.h"
//#include "Crystal/Space/Space/SignedDistanceCalculator.h"

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

DMBoundaryView::DMBoundaryView(const std::string& name, World* world, Renderer* renderer) :
	IOkCancelView(name),
	boxView("Box"),
	world(world),
	renderer(renderer)
{
	add(&boxView);
}

void DMBoundaryView::onOk()
{
	//const auto sphere = sphereView.getValue();
	const auto bb = boxView.getValue();

	auto scene = new BoundaryScene();

	DMBoundary boundary;
	boundary.addBox(bb);
	//SignedDistanceCalculator<float> c;
	SPHKernel kernel(1.0f);

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				const auto u = i / 10.0f;
				const auto v = j / 10.0f;
				const auto w = k / 10.0f;
				BoundaryNode node;
				node.position = bb.getPosition(u, v, w);
				const auto value = boundary.calculateWeight(node.position, 1.0f, 1.0f, kernel);
				node.value = value;//c.calculate(node.position, sphere);
				scene->add(node);
			}
		}
	}

	auto presenter = new BoundaryPresenter(scene, renderer->getPointRenderer());
	presenter->build();
	presenter->setMinMax(0.0f, 1.0f);//sphere.getRadius());
	presenter->send();

	scene->addPresenter(std::move(presenter));

	world->getRootScene()->addScene(scene);
}
