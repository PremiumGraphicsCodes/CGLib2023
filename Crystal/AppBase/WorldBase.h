#pragma once

#include "CGLib/Util/UnCopyable.h"
#include "Crystal/Scene/SceneGroup.h"
#include "Crystal/Scene/IAnimator.h"

namespace Crystal {
	namespace UI {

class WorldBase : private UnCopyable
{
public:
	WorldBase();

	virtual ~WorldBase() = default;

	Scene::SceneGroup* getRootScene() { return &rootScene; }

	int getNextId() { return nextId++; }

	void step();

	void addAnimator(Scene::IAnimator* animator) { animators.push_back(animator); }

	Graphics::Camera* getCamera() { return &camera; }

	//Crystal::Graphics::Camera* getCamera() { return &camera; }

private:
	Scene::SceneGroup rootScene;
	std::list<Scene::IAnimator*> animators;
	Graphics::Camera camera;
	int nextId = 0;
};
	}
}