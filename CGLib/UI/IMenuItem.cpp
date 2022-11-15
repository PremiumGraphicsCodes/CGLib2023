#include "IMenuItem.h"
#include "CGLib/UI/imgui.h"

using namespace Crystal::UI;

void IMenuItem::onShow()
{
	auto str = name.c_str();
	if (ImGui::MenuItem(str)) {
		onPushed();
	}
}