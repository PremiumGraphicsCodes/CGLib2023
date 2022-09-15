#include "Panel.h"

#include "CGLib/UI/imgui.h"

using namespace Crystal::UI;

void Panel::onShow()
{
	if (!name.empty()) {
		ImGui::Begin(name.c_str());
	}

	for (auto c : children) {
		c->show();
	}

	if (!name.empty()) {
		ImGui::End();
	}
}