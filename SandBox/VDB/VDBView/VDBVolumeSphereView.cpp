#include "VDBVolumeSphereView.h"

#include "../VDB/VDBVolume.h"
#include "World.h"

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::VDB;

VDBVolumeSphereView::VDBVolumeSphereView(const std::string& name, World* world) :
	IOkCancelView(name),
	world(world),
	scaleView("Scale", 1.0)
{
	add(&scaleView);
}

void VDBVolumeSphereView::onOk()
{
	auto volume = std::make_unique<VDBVolume>();
	for (int i = -5; i <= 5; ++i) {
		for (int j = -5; j <= 5; ++j) {
			for (int k = -5; k <= 5; ++k) {
				const auto dist = std::sqrt(i * i + j * j + k * k);
				const auto v = 1.0 - dist / 5.0;
				volume->setValue({ i,j,k }, v);
			}
		}
	}
	volume->setScale(scaleView.getValue());

	world->add(std::move(volume));
}