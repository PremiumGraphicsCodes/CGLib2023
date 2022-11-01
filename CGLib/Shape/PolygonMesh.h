#pragma once

#include "IVertex.h"
#include "IShape.h"
#include <vector>
#include <memory>

namespace Crystal {
	namespace Shape {

class PolygonMesh : public IShape
{
public:
	struct Face
	{
		int v0;
		int v1;
		int v2;
	};

	void add(std::unique_ptr<Shape::IVertex>&& v) { this->vertices.push_back(std::move(v)); }

	const std::vector<std::unique_ptr<Shape::IVertex>>& getVertices() const { return vertices; }

	void addFace(const Face& face) { this->faces.push_back(face); }

	std::vector<Face> getFaces() const { return faces; }

	Math::Box3df getBoundingBox() const override;

private:
	std::vector<Face> faces;
	std::vector<std::unique_ptr<Shape::IVertex>> vertices;

};

	}
}