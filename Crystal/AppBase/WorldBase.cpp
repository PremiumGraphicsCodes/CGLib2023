#include "WorldBase.h"
#include "Crystal/Scene/SceneBase.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WorldBase::WorldBase():
	camera(Vector3df(0, 0, 1), Vector3df(0, 0, 0), Vector3df(0, 1, 0), 0.1f, 10.0f)
{
	rootScene.setId(getNextId());
	rootScene.setName("Root");
}

void WorldBase::step()
{
	for (auto a : animators) {
		a->step();
	}
}