#pragma once

#include "CGLib/Util/UnCopyable.h"
#include "Crystal/Scene/Scene/SceneGroup.h"
#include "Crystal/Scene/Scene/IAnimator.h"

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

	void removeAnimator(Scene::IAnimator* animator);

	//Crystal::Graphics::Camera* getCamera() { return &camera; }

private:
	Scene::SceneGroup rootScene;
	std::list<Scene::IAnimator*> animators;
	int nextId = 0;
};
	}
}