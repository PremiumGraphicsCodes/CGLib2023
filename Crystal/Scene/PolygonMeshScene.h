#pragma once

#include "SceneBase.h"
#include "IVertex.h"
#include "PolygonMeshPresenter.h"
#include <vector>

namespace Crystal {
	namespace Scene {
		class IVertex;

class PolygonMeshScene : public SceneBase
{
public:
	struct Face
	{
		int v0;
		int v1;
		int v2;
	};

	void add(IVertex* v) { this->vertices.push_back(v); }

	std::vector<IVertex*> getVertices() const { return vertices; }

	void addFace(const Face& face) { this->faces.push_back(face); }

	std::vector<Face> getFaces() const { return faces; }

	void setPresenter(std::unique_ptr<PolygonMeshPresenter> p) { this->presenter = std::move(p); }

	IPresenter* getPresenter() override { return presenter.get(); }

private:
	std::vector<Face> faces;
	std::vector<IVertex*> vertices;
	std::unique_ptr<PolygonMeshPresenter> presenter;
};

	}
}