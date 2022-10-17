#include "Crystal/AppBase/Canvas.h"
#include "Crystal/AppBase/Window.h"
#include "Crystal/AppBase/CameraUICtrl.h"
#include "Crystal/AppBase/CameraMenu.h"
#include "Crystal/AppBase/SceneListPanel.h"

#include "CGLib/UI/Panel.h"
#include "World.h"
#include "Renderer.h"
#include "ShapeMenu.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;
//using namespace Crystal::Renderer;
using namespace Crystal::UI;

int main() {
	World world;
	Renderer renderer(&world);

	Crystal::UI::Canvas canvas;
	canvas.setUICtrl(std::make_unique<CameraUICtrl>(renderer.getCamera()));
	Crystal::UI::Window window("Hello", &world, &canvas, &renderer);
	window.init();

	auto control = new Panel("Control");

	window.add(new CameraMenu("Camera", &world, &renderer));

	window.add(new ShapeMenu("Shape", &world, &renderer, control));
	window.add(control);

	window.add(new SceneListPanel("SceneList", &world));
	
	window.show();
}