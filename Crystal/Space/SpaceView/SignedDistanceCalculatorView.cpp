#include "SignedDistanceCalculatorView.h"

#include "../Space/SignedDistanceCalculator.h"
#include "DistanceScene.h"
#include "DistancePresenter.h"
#include "World.h"
#include "Renderer.h"
#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::Space;

SignedDistanceCalculatorView::SignedDistanceCalculatorView(const std::string& name, World* world, Renderer* renderer) :
	IOkCancelView(name),
	sphereView("Sphere"),
	world(world),
	renderer(renderer)
{
	add(&sphereView);
}

void SignedDistanceCalculatorView::onOk()
{
	const auto sphere = sphereView.getValue();
	const auto bb = sphere.getBoundingBox();

	auto scene = new DistanceScene();

	SignedDistanceCalculator<float> c;

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				const auto u = i / 10.0f;
				const auto v = j / 10.0f;
				const auto w = k / 10.0f;
				DistanceNode node;
				node.position = bb.getPosition(u, v, w);
				node.value = c.calculate(node.position, sphere);
				scene->add(node);
			}
		}
	}

	auto presenter = new DistancePresenter(scene, renderer->getPointRenderer());
	presenter->build();
	presenter->setMinMax(-sphere.getRadius(), 0.0f);//sphere.getRadius());
	presenter->send();

	scene->addPresenter(std::move(presenter));

	world->getRootScene()->addScene(scene);

	//scene->Presenter(std::move(presenter));
}
