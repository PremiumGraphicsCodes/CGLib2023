#include "CtrlMenu.h"
#include "CGLib/UI/MenuItem.h"

#include "Renderer.h"

#include "Crystal/AppBase/Canvas.h"

#include "Crystal/AppBase/CameraUICtrl.h"
#include "Crystal/AppBase/PickUICtrl.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

CtrlMenu::CtrlMenu(const std::string& name, Canvas* canvas, Renderer* renderer) :
	IMenu(name)
{
	add(new MenuItem("Camera", [canvas]
		{
			auto ctrl = std::make_unique<CameraUICtrl>(canvas->getCamera());
			canvas->setUICtrl(std::move(ctrl));
		}));
	add(new MenuItem("Pick", [canvas, renderer]
		{
			auto ctrl = std::make_unique<PickUICtrl>(renderer->getIdTexture());
			canvas->setUICtrl(std::move(ctrl));
		}));
}