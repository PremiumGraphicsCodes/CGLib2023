#include "IWorld.h"
#include "Crystal/Scene/IScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

IWorld::IWorld() :
	camera(Vector3df(0, 0, 1), Vector3df(0, 0, 0), Vector3df(0, 1, 0), 0.1, 10.0)
{}

void IWorld::add(IScene* scene)
{
	rootScene.addScene(scene);
}
