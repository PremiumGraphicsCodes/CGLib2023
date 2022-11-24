#include "Crystal/AppBase/Canvas.h"
#include "Crystal/AppBase/Window.h"
#include "Crystal/AppBase/CameraMenu.h"
#include "Crystal/AppBase/CameraUICtrl.h"
#include "Crystal/AppBase/SceneListPanel.h"

#include "VDBPointsMenu.h"
#include "VDBVolumeMenu.h"

#include "CGLib/UI/Panel.h"

#include "World.h"
#include "Renderer.h"

#include <openvdb/openvdb.h>

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;
//using namespace Crystal::Renderer;
using namespace Crystal::UI;


int main() {
	openvdb::initialize();

	World world;
	Renderer renderer(&world);

	Crystal::UI::Canvas canvas;
	Crystal::UI::Window app("Hello", &world, &canvas, &renderer);
	app.init();

	auto control = new Panel("Control");
	auto listPanel = new SceneListPanel("Scenes", world.getRootScene());

	app.add(new CameraMenu("Camera", world.getRootScene(), canvas.getCamera()));
	app.add(new VDBPointsMenu("VDBPoints", &world, &renderer, control));
	app.add(new VDBVolumeMenu("VDBVolume", &world, &renderer, control));
	app.add(control);
	app.add(listPanel);

	app.show();
}