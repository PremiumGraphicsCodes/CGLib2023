#pragma once

#include "IVertex.h"
#include "IShape.h"
#include <vector>

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

	void add(Shape::IVertex* v) { this->vertices.push_back(v); }

	std::vector<Shape::IVertex*> getVertices() const { return vertices; }

	void addFace(const Face& face) { this->faces.push_back(face); }

	std::vector<Face> getFaces() const { return faces; }

	Math::Box3df getBoundingBox() const override;

private:
	std::vector<Face> faces;
	std::vector<Shape::IVertex*> vertices;

};

	}
}