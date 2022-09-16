#pragma once

#include "CGLib/Util/UnCopyable.h"
#include "Crystal/Scene/IScene.h"

namespace Crystal {
	namespace UI {

class IWorld : private UnCopyable
{
public:
	IWorld();

	virtual ~IWorld() = default;

	void add(Scene::IScene* scene);

	Scene::IScene rootScene;

	//Crystal::Graphics::Camera* getCamera() { return &camera; }

private:

};
	}
}