#include "CompactSpaceHashView.h"

//#include "Crystal/Scene/ParticleSystemScene.h"

#include "../Space/CompactSpaceHash.h"
#include "World.h"
#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

CompactSpaceHashView::CompactSpaceHashView(const std::string& name, World* world, Renderer* renderer) :
	IOkCancelView(name),
	psSelectView("ParticleSystem", world),
	searchRadiusView("SearchRadius", 1.0f),
	world(world),
	renderer(renderer)
{
	add(&psSelectView);
	add(&searchRadiusView);
}

void CompactSpaceHashView::onOk()
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
}
