﻿
#include "Crystal/AppBase/Canvas.h"

#include "Crystal/AppBase/CameraUICtrl.h"
#include "CGLib/UI/Panel.h"

#include <stdio.h>

#include "../Renderer/PointRenderer.h"
#include "../Renderer/LineRenderer.h"

#include "Crystal/AppBase/Window.h"
#include "Crystal/AppBase/IRenderer.h"
#include "Crystal/AppBase/MenuItem.h"

#include "Renderer.h"


#include <iostream>

#include "CGLib/Math/Vector2d.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;
//using namespace Crystal::Renderer;
using namespace Crystal::UI;


class ParticleSystemMenu : public IMenu
{
public:
	explicit ParticleSystemMenu(const std::string& name) :
		IMenu(name)
	{
		add(new MenuItem("Sphere", []() {}));

		/*
			add(new MenuItem("SpaceHash", [world, canvas, control]() {
				control->setWindow(new SpaceHashView("SpaceHash", world, canvas));
				}));
				*/
	}
};

int main() {
	Renderer renderer;
	auto uiCtrl = std::make_unique<Crystal::UI::CameraUICtrl>(renderer.getCamera());

	Crystal::UI::Canvas canvas(std::move(uiCtrl), &renderer);
	Crystal::UI::Window app("Hello", &canvas);
	app.init();

	//renderer.addParticleSystem();
	renderer.addWireFrame();

	app.add(new ParticleSystemMenu("ParticleSystem"));
	app.add(new Panel("Control"));
	
	app.show();
}