#include "WorldBase.h"
#include "Crystal/Scene/Scene/SceneBase.h"

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

void WorldBase::removeAnimator(IAnimator* animator)
{
	std::remove(animators.begin(), animators.end(), animator);
}
