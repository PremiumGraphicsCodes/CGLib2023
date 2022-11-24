#include "VDBPointsBoxView.h"

#include "../VDB/VDBPoints.h"
#include "World.h"

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::VDB;

VDBPointsBoxView::VDBPointsBoxView(const std::string& name, World* model, Renderer* canvas) :
	IOkCancelView(name),
	world(model),
	sphereView("Sphere"),
	divideLengthView("DivideLength", 0.1f)
{
	add(&sphereView);
	add(&divideLengthView);
}

void VDBPointsBoxView::onOk()
{
	const auto sphere = sphereView.getValue();
	const auto bb = sphere.getBoundingBox();

	std::vector<Vector3df> positions;
	const auto& length = bb.getLength();
	const auto divLength = divideLengthView.getValue();
	const auto du = divLength / length.x;
	const auto dv = divLength / length.y;
	const auto dw = divLength / length.z;
	const auto tolerance = 1.0e-12f;
	for (auto u = 0.0; u < 1.0 + tolerance; u += du) {
		for (auto v = 0.0; v < 1.0 + tolerance; v += dv) {
			for (auto w = 0.0; w < 1.0 + tolerance; w += dw) {
				const auto p = bb.getPosition(u, v, w);
				if (sphere.contains(p, tolerance)) {
					positions.push_back(p);
				}
			}
		}
	}

	auto points = std::make_unique<VDBPoints>();
	points->create(positions);

	world->add(std::move(points));
}