#include "WorldBase.h"
#include "Crystal/Scene/SceneBase.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WorldBase::WorldBase()
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