#pragma once

#include "SceneBase.h"
#include "CGLib/Shape/IVertex.h"
#include "PolygonMeshPresenter.h"
#include <vector>

namespace Crystal {
	namespace Shape {
		class IVertex;
	}
	namespace Scene {

class PolygonMeshScene : public SceneBase
{
public:
	struct Face
	{
		int v0;
		int v1;
		int v2;
	};

	void add(Shape::IVertex* v) { this->vertices.push_back(v); }

	std::vector<Shape::IVertex*> getVertices() const { return vertices; }

	void addFace(const Face& face) { this->faces.push_back(face); }

	std::vector<Face> getFaces() const { return faces; }

	void setPresenter(std::unique_ptr<PolygonMeshPresenter> p) { this->presenter = std::move(p); }

	IPresenter* getPresenter() override { return presenter.get(); }

private:
	std::vector<Face> faces;
	std::vector<Shape::IVertex*> vertices;
	std::unique_ptr<PolygonMeshPresenter> presenter;
};

	}
}