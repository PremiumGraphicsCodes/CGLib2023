#include "DensityEstimatorView.h"

#include "World.h"

//#include "Crystal/Scene/ParticleSystemScene.h"

#include "Crystal/Space/SpaceHash.h"
#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

DensityEstimatorView::DensityEstimatorView(const std::string& name, World* world, Renderer* renderer) :
	IOkCancelView(name),
	pcSelectView("PointCloud", world),
	searchRadiusView("SearchRadius", 1.0f),
	world(world),
	renderer(renderer)
{
	add(&pcSelectView);
	add(&searchRadiusView);
}

void DensityEstimatorView::onOk()
{
	/*
	auto psScene = world->getRootScene()->findSceneById<ParticleSystemScene*>(pcSelectView.getId());
	const auto& particles = psScene->getShape()->getParticles();
	SpaceHash spaceHash(searchRadiusView.getValue(), particles.size());
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
