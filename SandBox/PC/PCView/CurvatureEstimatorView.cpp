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
	pcIdView("PointCloudId", -1),
	searchRadiusView("SearchRadius", 1.5f),
	colorMapView("ColorMap"),
	world(world),
	renderer(renderer)
{
	add(&pcIdView);
	add(&searchRadiusView);
	add(&colorMapView);
}

void CurvatureEstimatorView::onOk()
{
	auto pointCloud = world->getRootScene()->findSceneById<PointCloudScene*>(pcIdView.getValue());
	if (pointCloud == nullptr) {
		return;
	}

	const auto& points = pointCloud->getShape()->getPoints();

	CurvatureEstimator estimator;
	for (const auto& p : points) {
		estimator.add(p->getPosition());
	}
	estimator.estimate(searchRadiusView.getValue());

	const auto curvatures = estimator.getCurvatures();

	auto colorMap = this->colorMapView.getValue();
	const auto min = *std::min_element(curvatures.begin(), curvatures.end());
	const auto max = *std::max_element(curvatures.begin(), curvatures.end());
	colorMap.setMin(min);
	colorMap.setMax(max);

	auto newPointCloud = std::make_unique<PointCloud>();
	for (int i = 0; i < points.size(); ++i) {
		const auto c = colorMap.getInterpolatedColor(curvatures[i]);
		newPointCloud->add(std::make_unique<Point>(points[i]->getPosition(), c));
	}

	pointCloud->setVisible(false);

	world->add(std::move(newPointCloud));
}