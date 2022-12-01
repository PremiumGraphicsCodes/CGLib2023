#pragma once

#include "Crystal/AppBase/WorldBase.h"
#include "Crystal/Scene/Scene/IPresenter.h"

#include "../VDB/VDBPoints.h"
#include "../VDB/VDBVolume.h"
#include "../VDB/VDBMesh.h"

#include <memory>
#include <vector>

namespace Crystal {
	namespace UI {
		class Renderer;

class World : public Crystal::UI::WorldBase
{
public:
	void setRenderer(Renderer* renderer) { this->renderer = renderer; }

	void add(std::unique_ptr<VDB::VDBPoints>&& points);

	void add(std::unique_ptr<VDB::VDBVolume>&& volume);

	void add(std::unique_ptr<VDB::VDBMesh>&& mesh);

	std::list<Scene::IPresenter*> getPresenters();

private:
	Renderer* renderer;
	std::vector<std::unique_ptr<Scene::IPresenter>> presenters;
	std::vector<std::unique_ptr<Scene::IPresenter>> idPresenters;
};

	}
}
