#include "Crystal/AppBase/Canvas.h"
#include "Crystal/AppBase/Window.h"
#include "Crystal/AppBase/CameraMenu.h"
#include "Crystal/AppBase/WorldBase.h"
#include "Crystal/AppBase/CameraUICtrl.h"

#include "PBRMenu.h"

#include "World.h"
#include "Renderer.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;
using namespace Crystal::UI;


int main() {
	World world;
	Renderer renderer(&world);

	Crystal::UI::Canvas canvas;
	Crystal::UI::Window app("Hello", &world, &canvas, &renderer);
	app.init();

	app.add(new CameraMenu("Camera", world.getRootScene(), canvas.getCamera()));
	app.add(new PBRMenu("PBR", &world, &renderer));

	app.show();
}