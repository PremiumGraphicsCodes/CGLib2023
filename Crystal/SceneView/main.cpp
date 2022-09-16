
#include "Crystal/AppBase/Canvas.h"

#include "Crystal/AppBase/CameraUICtrl.h"
#include "CGLib/UI/Panel.h"

#include <stdio.h>

#include "../Renderer/PointRenderer.h"
#include "../Renderer/LineRenderer.h"

#include "Crystal/AppBase/Window.h"
#include "Crystal/AppBase/IRenderer.h"
#include "Crystal/AppBase/MenuItem.h"

#include "ParticleSystemMenu.h"

#include "Renderer.h"

#include "PSBoxView.h"

#include <iostream>

#include "CGLib/Math/Vector2d.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;
//using namespace Crystal::Renderer;
using namespace Crystal::UI;


int main() {
	World world;
	Renderer renderer(&world);
	auto uiCtrl = std::make_unique<Crystal::UI::CameraUICtrl>(renderer.getCamera());

	Crystal::UI::Canvas canvas(std::move(uiCtrl), &renderer);
	Crystal::UI::Window app("Hello", &canvas);
	app.init();

	//renderer.addParticleSystem();
	renderer.addWireFrame();

	auto control = new Panel("Control");

	app.add(new ParticleSystemMenu("ParticleSystem", control, &world, &renderer));
	app.add(control);
	
	app.show();
}