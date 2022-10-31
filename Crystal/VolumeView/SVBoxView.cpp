#include "SVBoxView.h"

#include "World.h"
#include "Renderer.h"

#include "../Volume/SparseVolume.h"
#include "../Volume/SparseVolumeBuilder.h"

#include "SparseVolumeScene.h"
#include "SparseVolumePresenter.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

using namespace Crystal::Space;

SVBoxView::SVBoxView(const std::string& name, World* world, Renderer* canvas) :
	IOkCancelView(name),
	boxView("Box"),
	cellLengthView("Resolution", 1.0f),
	world(world),
	renderer(canvas)
{
	add(&boxView);
	boxView.setValue(Box3df(Vector3df(-10, -10, -10), Vector3df(10, 10, 10)));
	add(&cellLengthView);
}

void SVBoxView::onOk()
{
	//auto scene = world->getRootScene();

	const auto box = boxView.getValue();
	const auto cellLength = cellLengthView.getValue();

	SparseVolumeBuilder builder;
	builder.build({ cellLength, cellLength, cellLength }, 100);
	builder.add(box);
	auto sv = builder.get();
	auto nodes = sv->getNodes();
	for (auto n : nodes) {
		n->setValue(1.0f);
	}

	auto scene = new SparseVolumeScene();
	scene->setShape(std::move(sv));

	auto presenter = std::make_unique<SparseVolumePresenter>(scene, renderer->getPointRenderer());
	presenter->build();
	presenter->send();
	scene->setPresenter(std::move(presenter));
	world->getRootScene()->addScene(scene);

	//ISVAddView::addVolume(std::move(sv));
}