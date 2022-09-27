#pragma once

#include "CGLib/UI/IWindow.h"
#include "WorldBase.h"

namespace Crystal {
	namespace Scene {
		class SceneBase;
	}
	namespace UI {

class SceneListPanel : public IWindow
{
public:
	SceneListPanel(const std::string& name, WorldBase* model);

	void onShow() override;

private:
	void show(Scene::SceneBase* scene);

	WorldBase* world;
};

	}
}