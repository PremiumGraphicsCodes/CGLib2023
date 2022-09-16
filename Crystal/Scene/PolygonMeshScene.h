#pragma once

#include "IScene.h"
#include "IVertex.h"
#include "PolygonMeshPresenter.h"
#include <vector>

namespace Crystal {
	namespace Scene {
		class IVertex;

class PolygonMeshScene : public IScene
{
public:
	struct Face
	{
		int v0;
		int v1;
		int v2;
	};

	void add(IVertex* v);

	std::vector<IVertex*> getVertices() const { return vertices; }

	//void addIndex(const unsigned int index) { this->indices.push_back(index); }

	//std::vector<unsigned int> getIndices() const { return indices; }

	void setPresenter(std::unique_ptr<PolygonMeshPresenter> p) { this->presenter = std::move(p); }

	IPresenter* getPresenter() override { return presenter.get(); }

private:
	std::vector<Face> faces;
	std::vector<IVertex*> vertices;
	std::unique_ptr<PolygonMeshPresenter> presenter;
};

	}
}