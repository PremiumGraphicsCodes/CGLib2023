#include "CurvatureEstimatorView.h"

#include "World.h"

#include "../PC/CurvatureEstimator.h"

#include "PointCloudPresenter.h"
#include "PointCloudScene.h"

#include "Renderer.h"

#include "Crystal/Space/Space/SpaceHash.h"
#include <iostream>
#include <algorithm>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;
using namespace Crystal::PC;

CurvatureEstimatorView::CurvatureEstimatorView(const std::string& name, World* world, Renderer* renderer) :
	IOkCancelView(name),
	pcSelectView("PointCloud", world),
	searchRadiusView("SearchRadius", 1.5f),
	colorMapView("ColorMap"),
	world(world),
	renderer(renderer)
{
	add(&pcSelectView);
	add(&searchRadiusView);
	add(&colorMapView);
}

void CurvatureEstimatorView::onOk()
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
	CurvatureEstimator estimator;
	for (const auto& p : positions) {
		estimator.add(p);
	}
	estimator.estimate(searchRadiusView.getValue());

	const auto curvatures = estimator.getCurvatures();

	auto colorMap = this->colorMapView.getValue();
	const auto min = *std::min_element(curvatures.begin(), curvatures.end());
	const auto max = *std::max_element(curvatures.begin(), curvatures.end());
	colorMap.setMin(min);
	colorMap.setMax(max);

	auto pointCloud = std::make_unique<PointCloud>();
	//std::vector<ColorRGBAf> colors;
	for (int i = 0; i < positions.size(); ++i) {
		const auto c = colorMap.getInterpolatedColor(curvatures[i]);
		pointCloud->add(std::make_unique<Point>(positions[i], c));
		//colors.push_back(c);
	}

	auto scene = new PointCloudScene();
	scene->setShape(std::move(pointCloud));

	auto presenter = new PointCloudPresenter(scene, renderer->getPointRenderer());
	presenter->build();
	presenter->send();
	scene->addPresenter(presenter);
	world->getRootScene()->addScene(scene);

}