#include "VolumeMenu.h"

#include "CGLib/UI/Panel.h"
#include "Crystal/AppBase/MenuItem.h"

#include "SVBoxView.h"

using namespace Crystal::UI;

VolumeMenu::VolumeMenu(const std::string& name, Panel* control, World* world, Renderer* renderer) :
	IMenu(name)
{
	add(new MenuItem("SparseVolume", [&control, &world, &renderer]() {
		control->setChild(new SVBoxView("SVBox", world, renderer));
		}));
	/*
	add(new MenuItem("CompactSpaceHash", [control, world, renderer]() {
		control->setChild(new CompactSpaceHashView("CompactSpaceHash", world, renderer));
		}));
		*/
}
