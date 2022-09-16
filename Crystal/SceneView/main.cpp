#include "Crystal/AppBase/Canvas.h"
#include "Crystal/AppBase/Window.h"
#include "Crystal/AppBase/ParticleSystemMenu.h"

#include "CGLib/UI/Panel.h"

#include "WireFrameMenu.h"

#include "Renderer.h"

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

	auto control = new Panel("Control");

	app.add(new ParticleSystemMenu("ParticleSystem", control, &world, &renderer));
	app.add(new WireFrameMenu("WireFrame", control, &world, &renderer));
	app.add(control);
	
	app.show();
}