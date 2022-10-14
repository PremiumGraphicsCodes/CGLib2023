#include "StringView.h"

#include "imgui.h"

using namespace Crystal::UI;

void StringView::onShow()
{
	const char* s = value.c_str();
	char ss[256];
	strcpy_s(ss, s);
	if (ImGui::InputText(name.c_str(), ss, 256)) {
		value = ss;
	}
}