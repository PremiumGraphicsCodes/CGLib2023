#pragma once

#include "SceneBase.h"
#include "IVertex.h"
#include "WireFramePresenter.h"
#include <vector>

namespace Crystal {
	namespace Scene {
		class IVertex;

class WireFrameScene : public SceneBase
{
public:
	void add(IVertex* v);

	std::vector<IVertex*> getVertices() const { return vertices; }

	void addIndex(const unsigned int index) { this->indices.push_back(index); }

	std::vector<unsigned int> getIndices() const { return indices; }

	void setPresenter(std::unique_ptr<WireFramePresenter> p) { this->presenter = std::move(p); }

	IPresenter* getPresenter() override { return presenter.get(); }

private:
	std::vector<unsigned int> indices;
	std::vector<IVertex*> vertices;
	std::unique_ptr<WireFramePresenter> presenter;
};

	}
}