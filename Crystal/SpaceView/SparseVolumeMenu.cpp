#include "SparseVolumeMenu.h"

#include "CGLib/UI/Panel.h"
#include "Crystal/AppBase/MenuItem.h"

#include "SVBoxView.h"


using namespace Crystal::UI;

SparseVolumeMenu::SparseVolumeMenu(const std::string& name, Panel* control, World* world, Renderer* renderer) :
	IMenu(name)
{
	add(new MenuItem("SVBox", [&control, &world, &renderer]() {
		control->setChild(new SVBoxView("SVBox", world, renderer));
		}));
}
