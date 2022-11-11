#include "NormalEstimatorView.h"

#include "World.h"

#include "../PC/NormalEstimator.h"

#include "PointCloudPresenter.h"
#include "PointCloudScene.h"

#include "Renderer.h"

#include "Crystal/Space/SpaceHash.h"
#include <iostream>
#include <algorithm>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;
using namespace Crystal::PC;

NormalEstimatorView::NormalEstimatorView(const std::string& name, World* world, Renderer* renderer) :
	IOkCancelView(name),
	pcSelectView("PointCloud", world),
	searchRadiusView("SearchRadius", 1.5f),
	world(world),
	renderer(renderer)
{
	add(&pcSelectView);
	add(&searchRadiusView);
}

void NormalEstimatorView::onOk()
{
	std::vector<Vector3df> positions;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				const auto x = i * 1.0f;
				const auto y = j * 1.0f;
				const auto z = k * 1.0f;
				positions.emplace_back(x, y, z);
			}
		}
	}
	NormalEstimator estimator;
	for (const auto& p : positions) {
		estimator.add(p);
	}
	estimator.estimate(searchRadiusView.getValue());

	/*
	const auto densities = estimator.getDensities();

	auto colorMap = this->colorMapView.getValue();
	const auto min = *std::min_element(densities.begin(), densities.end());
	const auto max = *std::max_element(densities.begin(), densities.end());
	colorMap.setMin(min);
	colorMap.setMax(max);

	auto pointCloud = std::make_unique<PointCloud>();
	//std::vector<ColorRGBAf> colors;
	for (int i = 0; i < positions.size(); ++i) {
		const auto c = colorMap.getInterpolatedColor(densities[i]);
		pointCloud->add(std::make_unique<Point>(positions[i], c));
		//colors.push_back(c);
	}

	auto scene = new PointCloudScene();
	scene->setShape(std::move(pointCloud));

	auto presenter = std::make_unique<PointCloudPresenter>(scene, renderer->getPointRenderer());
	presenter->build();
	presenter->send();
	scene->setPresenter(std::move(presenter));
	world->getRootScene()->addScene(scene);
	*/
}