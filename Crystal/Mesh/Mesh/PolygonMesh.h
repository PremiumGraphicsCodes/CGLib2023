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
		int positionIndex;
		int normalIndex;
		int texCoordIndex;
	};

	PolygonMesh();

	//PolygonMesh(const std::vector<Face>& faces, std::vector<std::unique_ptr<Vertex>>&& vertices);

	void addPosition(const Math::Vector3df& p) { this->positions.push_back(p); }

	void addNormal(const Math::Vector3df& n) { this->normals.push_back(n); }

	void addTexCoord(const Math::Vector2df& t) { this->texCoords.push_back(t); }

	void addVertex(const Vertex& v) { this->vertices.push_back(v); }

	void addFace(const Face& face) { this->faces.push_back(face); }

	//const std::vector<Vertex>& getVertices() const { return vertices; }

	Math::Vector3df getPosition(const int index) const { return positions[index]; }

	std::vector<Face> getFaces() const { return faces; }

	Math::Box3df getBoundingBox() const;

	//std::vector<Face> getFaces() const { return faces; }

	std::vector<Math::Vector3df> getPositions() const { return positions; }

	std::vector<Math::Vector3df> getNormals() const { return normals; }

	std::vector<Math::Vector2df> getTexCoords() const { return texCoords; }

	std::vector<Vertex> getVertices() const { return vertices; }

private:
	std::vector<Face> faces;
	std::vector<Math::Vector3df> positions;
	std::vector<Math::Vector3df> normals;
	std::vector<Math::Vector2df> texCoords;
	std::vector<Vertex> vertices;
};

	}
}