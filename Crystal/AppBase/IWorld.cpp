#include "IWorld.h"
#include "Crystal/Scene/IScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

IWorld::IWorld()
{}

void IWorld::add(IScene* scene)
{
	rootScene.addScene(scene);
}
