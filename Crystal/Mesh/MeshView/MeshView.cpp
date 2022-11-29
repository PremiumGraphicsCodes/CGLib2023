#include "Crystal/AppBase/Canvas.h"
#include "Crystal/AppBase/Window.h"
#include "Crystal/AppBase/CameraMenu.h"
#include "Crystal/AppBase/CameraUICtrl.h"
#include "Crystal/AppBase/SceneListPanel.h"

#include "CGLib/UI/Panel.h"

#include "World.h"
#include "Renderer.h"

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
	auto listPanel = new SceneListPanel("Scenes", world.getRootScene());

	//app.add(new FileMenu("File", &world, &renderer));
	app.add(new CameraMenu("Camera", world.getRootScene(), canvas.getCamera()));
	//app.add(new PCMenu("PC", &world, &renderer, control));
	app.add(control);
	app.add(listPanel);

	app.show();
}