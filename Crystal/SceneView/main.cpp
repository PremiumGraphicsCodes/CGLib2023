
#include "Crystal/AppBase/Canvas.h"

#include "Crystal/AppBase/CameraUICtrl.h"
#include "CGLib/UI/Panel.h"

#include "Crystal/AppBase/Window.h"

#include "ParticleSystemMenu.h"
#include "WireFrameMenu.h"

#include "Renderer.h"

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

	Crystal::UI::Canvas canvas(&renderer);
	Crystal::UI::Window app("Hello", &canvas);
	app.init();

	//renderer.addParticleSystem();
	//renderer.addWireFrame();

	auto control = new Panel("Control");

	app.add(new ParticleSystemMenu("ParticleSystem", control, &world, &renderer));
	app.add(new WireFrameMenu("WireFrame", control, &world, &renderer));
	app.add(control);
	
	app.show();
}