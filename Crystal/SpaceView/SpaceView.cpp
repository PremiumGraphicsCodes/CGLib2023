#include "Crystal/AppBase/Canvas.h"
#include "Crystal/AppBase/Window.h"
#include "Crystal/AppBase/CameraMenu.h"
#include "Crystal/AppBase/ShapeMenu.h"
#include "Crystal/AppBase/WorldBase.h"
#include "Crystal/AppBase/RendererBase.h"
#include "Crystal/AppBase/CameraUICtrl.h"

#include "CGLib/UI/Panel.h"

#include "SpaceMenu.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;
//using namespace Crystal::Renderer;
using namespace Crystal::UI;

namespace {
	class World : public Crystal::UI::WorldBase
	{
	public:
	};

	class Renderer : public Crystal::UI::RendererBase
	{
	public:
		explicit Renderer(World* world) :
			RendererBase(world)
		{}

		void onInit() override
		{

		}

	private:

	};
}

int main() {
	World world;
	Renderer renderer(&world);

	Crystal::UI::Canvas canvas;
	canvas.setUICtrl(std::make_unique<CameraUICtrl>(renderer.getCamera()));
	Crystal::UI::Window app("Hello", &canvas, &renderer);
	app.init();

	auto control = new Panel("Control");

	app.add(new ShapeMenu("Camera", &world, &renderer, control));
	app.add(new ShapeMenu("Shape", &world, &renderer, control));
	app.add(new SpaceMenu("Space", control, &world, &renderer));
	app.add(control);

	app.show();
}