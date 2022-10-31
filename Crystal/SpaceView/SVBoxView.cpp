#include "SVBoxView.h"

//#include "../Volume/SparseVolume.h"
//#include "../Volume/SparseVolumeBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

using namespace Crystal::Math;
using namespace Crystal::UI;

SVBoxView::SVBoxView(const std::string& name, World* world, Renderer* canvas) :
	IOkCancelView(name),
	boxView("Box"),
	cellLengthView("Resolution", 1.0f)
{
	add(&boxView);
	boxView.setValue(Box3df(Vector3df(-10, -10, -10), Vector3df(10, 10, 10)));
	add(&cellLengthView);
}

void SVBoxView::onOk()
{
	/*
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

	//ISVAddView::addVolume(std::move(sv));
	*/
}