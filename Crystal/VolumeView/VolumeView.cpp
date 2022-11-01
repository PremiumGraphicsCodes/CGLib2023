﻿#include "Crystal/AppBase/Canvas.h"
#include "Crystal/AppBase/Window.h"
#include "Crystal/AppBase/CameraMenu.h"
#include "Crystal/AppBase/CameraUICtrl.h"

#include "CGLib/UI/Panel.h"

#include "World.h"
#include "Renderer.h"

#include "SparseVolumeMenu.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;
//using namespace Crystal::Renderer;
using namespace Crystal::UI;


int main() {
	World world;
	Renderer renderer(&world);

	Canvas canvas(&world);
	Window app("Hello", &world, &canvas, &renderer);
	app.init();

	auto control = new Panel("Control");

	app.add(new CameraMenu("Camera", &world));
	app.add(new SparseVolumeMenu("SparseVolume", control, &world, &renderer));
	app.add(control);

	app.show();
}