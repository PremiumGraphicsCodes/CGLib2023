#include "DensityEstimatorView.h"

#include "World.h"

#include "../PC/DensityEstimator.h"

#include "Crystal/Space/SpaceHash.h"
#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;
using namespace Crystal::PC;

DensityEstimatorView::DensityEstimatorView(const std::string& name, World* world, Renderer* renderer) :
	IOkCancelView(name),
	pcSelectView("PointCloud", world),
	searchRadiusView("SearchRadius", 1.5f),
	world(world),
	renderer(renderer)
{
	add(&pcSelectView);
	add(&searchRadiusView);
}

void DensityEstimatorView::onOk()
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
	DensityEstimator estimator;
	for (const auto& p : positions) {
		estimator.add(p);
	}
	estimator.estimate(searchRadiusView.getValue());
}