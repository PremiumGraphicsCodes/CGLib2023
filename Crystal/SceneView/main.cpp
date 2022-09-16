﻿#include "Crystal/AppBase/Canvas.h"
#include "Crystal/AppBase/Window.h"
#include "Crystal/AppBase/ParticleSystemMenu.h"
#include "Crystal/AppBase/WireFrameMenu.h"
#include "Crystal/AppBase/IWorld.h"

#include "CGLib/UI/Panel.h"



using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;
//using namespace Crystal::Renderer;
using namespace Crystal::UI;

namespace {
	class World : public Crystal::UI::IWorld
	{
		public:
	};

	class Renderer : public Crystal::UI::IRenderer
	{
	public:
		explicit Renderer(World* world) :
			IRenderer(world)
		{}

		void onInit() override
		{

		}

	private:

	};
}

#include "Crystal/AppBase/CameraUICtrl.h"

int main() {
	World world;
	Renderer renderer(&world);

	Crystal::UI::Canvas canvas;
	canvas.setUICtrl(std::make_unique<CameraUICtrl>(renderer.getCamera()));
	Crystal::UI::Window app("Hello", &canvas, &renderer);
	app.init();

	auto control = new Panel("Control");

	app.add(new ParticleSystemMenu("ParticleSystem", control, &world, &renderer));
	app.add(new WireFrameMenu("WireFrame", control, &world, &renderer));
	app.add(control);
	
	app.show();
}