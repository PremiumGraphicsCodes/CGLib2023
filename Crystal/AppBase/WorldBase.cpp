#include "WorldBase.h"
#include "Crystal/Scene/IScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WorldBase::WorldBase()
{}

void WorldBase::add(IScene* scene)
{
	rootScene.addScene(scene);
}
