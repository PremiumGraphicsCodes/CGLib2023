#include "IMenu.h"
#include "CGLib/UI/imgui.h"

using namespace Crystal::UI;

void IMenu::onShow()
{
	const auto& c = name.c_str();
	if (ImGui::BeginMenu(c)) {
		for (auto c : children) {
			c->show();
		}
		ImGui::EndMenu();
	}
}