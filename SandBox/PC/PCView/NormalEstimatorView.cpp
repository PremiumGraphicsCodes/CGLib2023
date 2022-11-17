#include "NormalEstimatorView.h"

#include "World.h"

#include "../PC/NormalEstimator.h"

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

NormalEstimatorView::NormalEstimatorView(const std::string& name, World* world, Renderer* renderer) :
	IOkCancelView(name),
	pcIdView("PointCloudId", -1),
	searchRadiusView("SearchRadius", 1.5f),
	world(world),
	renderer(renderer)
{
	add(&pcIdView);
	add(&searchRadiusView);
}

void NormalEstimatorView::onOk()
{
	auto pointCloud = world->getRootScene()->findSceneById<PointCloudScene*>(pcIdView.getValue());
	if (pointCloud == nullptr) {
		return;
	}

	const auto& points = pointCloud->getShape()->getPoints();
	NormalEstimator estimator;
	for (const auto& p : points) {
		estimator.add(p->getPosition());
	}
	estimator.estimate(searchRadiusView.getValue());

	const auto normals = estimator.getNormals();

	auto newPointCloud = std::make_unique<PointCloud>();
	for (int i = 0; i < points.size(); ++i) {
		const ColorRGBAf c( normals[i], 0.0f );
		newPointCloud->add(std::make_unique<Point>(points[i]->getPosition(), c));
	}

	world->add(std::move(newPointCloud));

	pointCloud->setVisible(false);
}