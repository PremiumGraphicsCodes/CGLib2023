#pragma once

#include "IMenu.h"
#include "CGLib/Graphics/Camera.h"

namespace Crystal {
	namespace UI {
		class WorldBase;

class CameraMenu : public IMenu
{
public:
	CameraMenu(const std::string& name, WorldBase* world, Graphics::Camera* camera);

private:
	void onFit();

	void onXY();

	void onYZ();

	void onZX();

	WorldBase* world;
	Graphics::Camera* camera;
};

	}
}