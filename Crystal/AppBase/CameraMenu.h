#pragma once

#include "IMenu.h"
#include "CGLib/Graphics/Camera.h"
#include "Crystal/Scene/SceneGroup.h"

namespace Crystal {
	namespace UI {

class CameraMenu : public IMenu
{
public:
	CameraMenu(const std::string& name, Scene::SceneGroup* rootScene, Graphics::Camera* camera);

private:
	void onFit();

	void onXY();

	void onYZ();

	void onZX();

	Scene::SceneGroup* rootScene;
	Graphics::Camera* camera;
};

	}
}