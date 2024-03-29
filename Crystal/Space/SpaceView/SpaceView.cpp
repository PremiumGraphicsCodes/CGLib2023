﻿#include "Crystal/AppBase/Canvas.h"
#include "Crystal/AppBase/Window.h"
#include "Crystal/AppBase/CameraMenu.h"
#include "Crystal/AppBase/WorldBase.h"
#include "Crystal/AppBase/CameraUICtrl.h"

#include "CGLib/UI/Panel.h"

#include "World.h"
#include "Renderer.h"

#include "SpaceMenu.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;
//using namespace Crystal::Renderer;
using namespace Crystal::UI;


int main() {
	World world;
	Renderer renderer(&world);

	Crystal::UI::Canvas canvas;
	Crystal::UI::Window app("Hello", &world, &canvas, &renderer);
	app.init();

	auto control = new Panel("Control");

	app.add(new CameraMenu("Camera", world.getRootScene(), canvas.getCamera()));
	app.add(new SpaceMenu("Space", control, &world, &renderer));
	app.add(control);

	app.show();
}