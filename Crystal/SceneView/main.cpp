#include "Crystal/AppBase/Canvas.h"
#include "Crystal/AppBase/Window.h"
#include "Crystal/AppBase/ParticleSystemMenu.h"
#include "Crystal/AppBase/WireFrameMenu.h"
#include "Crystal/AppBase/WorldBase.h"
#include "Crystal/AppBase/RendererBase.h"
#include "Crystal/AppBase/CameraUICtrl.h"
#include "Crystal/AppBase/CameraMenu.h"

#include "CGLib/UI/Panel.h"


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
	Crystal::UI::Window window("Hello", &canvas, &renderer);
	window.init();

	auto control = new Panel("Control");

	window.add(new CameraMenu("Camera", &world, &renderer));

	window.add(new ParticleSystemMenu("ParticleSystem", control, &world, &renderer));
	window.add(new WireFrameMenu("WireFrame", control, &world, &renderer));
	window.add(control);
	
	window.show();
}