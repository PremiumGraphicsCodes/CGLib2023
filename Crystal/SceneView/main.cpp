#include "Crystal/AppBase/Canvas.h"
#include "Crystal/AppBase/Window.h"
#include "Crystal/AppBase/CameraUICtrl.h"
#include "Crystal/AppBase/CameraMenu.h"
#include "Crystal/AppBase/SceneListPanel.h"

#include "CGLib/UI/Panel.h"
#include "World.h"
#include "Renderer.h"
#include "ShapeMenu.h"
#include "RendererMenu.h"
#include "CtrlMenu.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;
//using namespace Crystal::Renderer;
using namespace Crystal::UI;

int main() {
	World world;
	Renderer renderer(&world);

	Crystal::UI::Canvas canvas;
	Crystal::UI::Window window("Hello", &world, &canvas, &renderer);
	window.init();

	auto control = new Panel("Control");

	window.add(new CameraMenu("Camera", world.getRootScene(), canvas.getCamera()));
	window.add(new RendererMenu("Renderer", &world, &renderer));
	window.add(new CtrlMenu("Ctrl", &canvas));
	window.add(new ShapeMenu("Shape", &world, &renderer, control));
	window.add(new SceneListPanel("SceneList", world.getRootScene()));

	window.add(control);
	
	window.show();
}