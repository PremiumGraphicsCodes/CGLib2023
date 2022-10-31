#include "SPHVolumeConverterView.h"

#include "../Fluid/SPHVolumeConverter.h"

#include "SPHVolumeScene.h"
#include "CGLib/Math/Sphere3d.h"
#include "Renderer.h"
#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;
using namespace Crystal::Renderer;
using namespace Crystal::Physics;

namespace {
	constexpr auto tolerance = 1.0e-12;

	/*
	void build(const Sphere3dd& sphere, const int unum, const int vnum, const Matrix3dd& m, WireFrameBuilder& wfBuilder)
	{
		const auto du = 1.0 / static_cast<double>(unum);
		const auto dv = 1.0 / static_cast<double>(vnum);

		std::vector<std::vector<int>> grid;
		for (auto u = 0.0; u < 1.0 + tolerance; u += du) {
			std::vector<int> g;
			for (auto v = 0.0; v < 1.0 + tolerance; v += dv) {
				auto p = sphere.getPosition(u, v);
				p -= sphere.getCenter();
				p = m * p * glm::determinant(m);
				p += sphere.getCenter();
				g.push_back(wfBuilder.createPosition(p));
			}
			grid.push_back(g);
		}
		for (int i = 0; i < grid.size() - 1; ++i) {
			for (int j = 0; j < grid[i].size() - 1; ++j) {
				const auto v1 = grid[i][j];
				const auto v2 = grid[i + 1][j];
				const auto v3 = grid[i + 1][j + 1];
				const auto v4 = grid[i][j + 1];
				wfBuilder.addEdge(WireFrameEdge(v1, v2));
				wfBuilder.addEdge(WireFrameEdge(v2, v3));
				wfBuilder.addEdge(WireFrameEdge(v3, v4));
				wfBuilder.addEdge(WireFrameEdge(v4, v1));
			}
		}
	}
	*/
}

SPHVolumeConverterView::SPHVolumeConverterView(const std::string& name, World* model, Renderer* canvas) :
	IOkCancelView(name),
	world(model),
	renderer(canvas),
	particleRadiusView("ParticleRadius", 1.0f),
	cellLengthView("CellLength", 1.0),
	thresholdView("Threshold", 1.0f),
	colorMapView("ColorMap")
{
	add(&particleRadiusView);
	add(&cellLengthView);
	add(&thresholdView);
	add(&colorMapView);
}

void SPHVolumeConverterView::onOk()
{
	std::vector<Vector3dd> positions;

	const Sphere3df sphere(Vector3df(50, 50, 50), 10.0);
	const Box3df box = sphere.getBoundingBox();
	const auto center = sphere.getCenter();
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				const auto u = i / 10.0;
				const auto v = j / 10.0;
				const auto w = k / 10.0;
				const auto p = box.getPosition(u, v, w);
				if (sphere.contains(p, tolerance)) {
					positions.push_back(p);
				}
			}
		}
	}

	SPHVolumeConverter builder;
	auto sp = builder.buildIsotoropic(positions, particleRadiusView.getValue(), cellLengthView.getValue());
	//auto sp = builder.buildAnisotoropic(positions, particleRadiusView.getValue(), cellLengthView.getValue());

	//auto volumes = builder.getVolumes();
	const auto nodes = sp->getNodes();
	float maxValue = std::numeric_limits<float>::lowest();
	float minValue = std::numeric_limits<float>::max();
	for (auto n : nodes) {
		maxValue = std::max(maxValue, n->getValue());
		minValue = std::min(minValue, n->getValue());
	}
	std::cout << minValue << std::endl;
	std::cout << maxValue << std::endl;

	auto volume = new SPHVolumeScene();
	volume->setShape(std::move(sp));

	auto presenter = std::make_unique<SPHVolumePresenter>(volume, renderer->getPointRenderer());
	presenter->build();
	presenter->send();
	volume->setPresenter(std::move(presenter));
	world->getRootScene()->addScene(volume);
}