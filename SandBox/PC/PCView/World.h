#pragma once

#include "Crystal/AppBase/WorldBase.h"
#include "Crystal/Scene/IPresenter.h"
#include "PointCloudScene.h"
#include <memory>
#include <vector>

namespace Crystal {
	namespace UI {
		class Renderer;

class World : public Crystal::UI::WorldBase
{
public:
	void setRenderer(Renderer* renderer) { this->renderer = renderer; }

	void add(std::unique_ptr<PC::PointCloud>&& pointCloud);

private:
	Renderer* renderer;
	std::vector<std::unique_ptr<Scene::IPresenter>> presenters;
	std::vector<std::unique_ptr<Scene::IPresenter>> idPresenters;

};

	}
}
