#pragma once

#include "PolygonMesh.h"
#include "CGLib/Util/UnCopyable.h"
#include <memory>

namespace Crystal {
	namespace Math {
		template<typename T>
		class IVolume3d;
		template<typename T>
		class ISurface3d;
	}
	namespace Shape {

class PolygonMeshBuilder : private UnCopyable
{
public:
	PolygonMeshBuilder();

	void add(const Math::ISurface3d<float>& surface, const int unum, const int vnum);

	std::unique_ptr<PolygonMesh> build();

	int createVertex(const Math::Vector3df& position, const Math::Vector3df& normal, const Math::Vector2df& texCoord);

	int createFace(int v0, int v1, int v2);

	void createFaces(int v0, int v1, int v2, int v3);

	std::vector<PolygonMesh::Vertex> getVertices() const { return vertices; }

	std::vector<PolygonMesh::Face> getFaces() const { return faces; }

private:
	void add(const int v0, const int v1, const int v2, const int v3);

	Math::Vector3dd calculateNormal(const int v0, const int v1, const int v2);

	std::vector<PolygonMesh::Vertex> vertices;
	std::vector<PolygonMesh::Face> faces;
};

	}
}