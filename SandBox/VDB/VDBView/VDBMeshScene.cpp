#include "VDBMeshScene.h"

#include "../VDB/VDBMesh.h"

using namespace Crystal::Math;
using namespace Crystal::VDB;

Box3df VDBMeshScene::getBoundingBox() const
{
	return shape->getBoundingBox();
}