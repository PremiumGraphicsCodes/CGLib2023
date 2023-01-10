#pragma once

#include "Crystal/Scene/Scene/SceneBase.h"
//#include "DistancePresenter.h"
#include <vector>

namespace Crystal {
	namespace UI {

struct BoundaryNode
{
	Math::Vector3df position;
	float value;
};

class BoundaryScene : public Scene::SceneBase
{
public:
	BoundaryScene() = default;

	void add(const BoundaryNode& node) { this->nodes.push_back(node); }

	std::vector<BoundaryNode> getNodes() const { return nodes; }

	Math::Box3df getBoundingBox() const override;

private:
	std::vector<BoundaryNode> nodes;
};

	}
}