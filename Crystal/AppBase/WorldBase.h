#pragma once

#include "CGLib/Util/UnCopyable.h"
#include "Crystal/Scene/RootScene.h"

namespace Crystal {
	namespace UI {

class WorldBase : private UnCopyable
{
public:
	WorldBase();

	virtual ~WorldBase() = default;

	void add(Scene::IScene* scene);

	Scene::RootScene* getRootScene() { return &rootScene; }

	//Crystal::Graphics::Camera* getCamera() { return &camera; }

private:
	Scene::RootScene rootScene;

};
	}
}