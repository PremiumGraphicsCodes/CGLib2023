#pragma once

#include "SceneBase.h"
#include "CGLib/Shape/IVertex.h"
#include "WireFramePresenter.h"
#include <vector>

namespace Crystal {
	namespace Shape {
		class IVertex;
	}
	namespace Scene {

class WireFrameScene : public SceneBase
{
public:
	void add(Shape::IVertex* v);

	std::vector<Shape::IVertex*> getVertices() const { return vertices; }

	void addIndex(const unsigned int index) { this->indices.push_back(index); }

	std::vector<unsigned int> getIndices() const { return indices; }

	void setPresenter(std::unique_ptr<WireFramePresenter> p) { this->presenter = std::move(p); }

	IPresenter* getPresenter() override { return presenter.get(); }

private:
	std::vector<unsigned int> indices;
	std::vector<Shape::IVertex*> vertices;
	std::unique_ptr<WireFramePresenter> presenter;
};

	}
}