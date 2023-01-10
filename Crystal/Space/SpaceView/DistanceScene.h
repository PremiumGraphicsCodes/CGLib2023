#pragma once

#include "Crystal/Scene/Scene/SceneBase.h"
//#include "DistancePresenter.h"
#include <vector>

namespace Crystal {
	namespace Space {

struct DistanceNode
{
	Math::Vector3df position;
	float value;
};

class DistanceScene : public Scene::SceneBase
{
public:
	DistanceScene() = default;

	void add(const DistanceNode& node) { this->nodes.push_back(node); }

	std::vector<DistanceNode> getNodes() const { return nodes; }

	Math::Box3df getBoundingBox() const override;

private:
	std::vector<DistanceNode> nodes;
};

	}
}