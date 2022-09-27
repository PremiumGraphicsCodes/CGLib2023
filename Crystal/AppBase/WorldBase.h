#pragma once

#include "CGLib/Util/UnCopyable.h"
#include "Crystal/Scene/SceneGroup.h"

namespace Crystal {
	namespace UI {

class WorldBase : private UnCopyable
{
public:
	WorldBase();

	virtual ~WorldBase() = default;

	Scene::SceneGroup* getRootScene() { return &rootScene; }

	int getNextId() { return nextId++; }

	//Crystal::Graphics::Camera* getCamera() { return &camera; }

private:
	Scene::SceneGroup rootScene;
	int nextId = 0;
};
	}
}