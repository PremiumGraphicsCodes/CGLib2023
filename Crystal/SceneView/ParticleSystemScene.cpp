#include "ParticleSystemScene.h"

#include <cassert>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;


ParticleSystemScene::ParticleSystemScene()
{
	//assert(false);
}

Box3df ParticleSystemScene::getBoundingBox() const
{
	return shape->getBoundingBox();
}