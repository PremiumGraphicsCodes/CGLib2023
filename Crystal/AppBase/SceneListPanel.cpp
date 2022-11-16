#include "SceneListPanel.h"

#include "CGLib/UI/imgui.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

SceneListPanel::SceneListPanel(const std::string& name, Scene::SceneBase* scene) :
	IWindow(name),
	scene(scene)
{
}

void SceneListPanel::onShow()
{
	ImGui::Begin("SceneList");
	show(scene);
	ImGui::End();
}

void SceneListPanel::show(SceneBase* scene)
{
	const auto& name = scene->getName();
	const auto str = name.c_str();
	const auto id = scene->getId();

	if (ImGui::TreeNode(str)) {
		const auto& children = scene->getChildren();
		for (auto child : children) {
			show(child);
		}
		ImGui::TreePop();
	}
}