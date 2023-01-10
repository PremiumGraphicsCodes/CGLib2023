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
	/*
	auto psScene = world->getRootScene()->findSceneById<ParticleSystemScene*>(psSelectView.getId());
	const auto& particles = psScene->getShape()->getParticles();
	CompactSpaceHash spaceHash(searchRadiusView.getValue(), particles.size());
	for (const auto& p : particles) {
		spaceHash.add(p->getPosition());
	}
	int totalIndicesCount = 0;
	for (const auto& p : particles) {
		const auto indices = spaceHash.findNeighborIndices(p->getPosition());
		totalIndicesCount += indices.size();
	}
	std::cout << totalIndicesCount << std::endl;
	*/

	auto scene = new DistanceScene();
	DistanceNode node;
	node.position = Vector3df(0, 0, 0);
	node.value = 1.0f;
	scene->add(node);

	auto presenter = new DistancePresenter(scene, renderer->getPointRenderer());
	presenter->build();
	presenter->send();

	scene->addPresenter(std::move(presenter));

	world->getRootScene()->addScene(scene);

	//scene->Presenter(std::move(presenter));
}
