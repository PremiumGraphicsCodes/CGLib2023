#pragma once

#include "Crystal/Scene/Scene/SceneBase.h"
//#include "DistancePresenter.h"
#include <vector>

namespace Crystal {
	namespace Scene {

struct DistanceNode
{
	Math::Vector3df position;
	float value;
};

class DistanceScene : public SceneBase
{
public:
	DistanceScene() = default;

	void add(const DistanceNode& node) { this->nodes.push_back(node); }

	Math::Box3df getBoundingBox() const override;

private:
	std::vector<DistanceNode> nodes;
};

	}
}