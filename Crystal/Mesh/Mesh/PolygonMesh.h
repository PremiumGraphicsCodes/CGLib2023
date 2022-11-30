#pragma once

#include "CGLib/Math/Box3d.h"
#include <vector>
#include <memory>

namespace Crystal {
	namespace Mesh {

class PolygonMesh
{
public:
	struct Face
	{
		int v0;
		int v1;
		int v2;
	};

	struct Vertex
	{
		Math::Vector3df position;
		Math::Vector3df normal;
		Math::Vector2df texCoord;
	};

	PolygonMesh();

	//PolygonMesh(const std::vector<Face>& faces, std::vector<std::unique_ptr<Vertex>>&& vertices);

	void addVertex(std::unique_ptr<Vertex>&& v) { this->vertices.push_back(std::move(v)); }

	const std::vector<std::unique_ptr<Vertex>>& getVertices() const { return vertices; }

	void addFace(const Face& face) { this->faces.push_back(face); }

	std::vector<Face> getFaces() const { return faces; }

	Math::Box3df getBoundingBox() const;

private:
	std::vector<Face> faces;
	std::vector<std::unique_ptr<Vertex>> vertices;
};

	}
}