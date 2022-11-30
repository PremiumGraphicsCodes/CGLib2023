#pragma once

#include "PolygonMesh.h"
#include "CGLib/Util/UnCopyable.h"
#include <memory>

namespace Crystal {
	namespace Math {
		//template<typename T>
		//class ISurface3d;
		template<typename T>
		class Box3d;
		template<typename T>
		class Sphere3d;
	}
	namespace Mesh {

class PolygonMeshBuilder : private UnCopyable
{
public:
	PolygonMeshBuilder();

	void add(const Math::Sphere3d<float>& surface, const int unum, const int vnum);

	void add(const Math::Box3d<float>& box);

	std::unique_ptr<PolygonMesh> build();

	int createFace(int v0, int v1, int v2);

	void createFaces(int v0, int v1, int v2, int v3);

	int createPosition(const Math::Vector3df& v);

	int createNormal(const Math::Vector3df& v);

	int createTexCoord(const Math::Vector2df& v);

	int createVertex(const int positionId, const int normalId, const int texCoordId);

private:
	void add(const int v0, const int v1, const int v2, const int v3);

	Math::Vector3dd calculateNormal(const int v0, const int v1, const int v2);

	std::vector<Math::Vector3df> positions;
	std::vector<Math::Vector3df> normals;
	std::vector<Math::Vector2df> texCoords;
	std::vector<PolygonMesh::Vertex> vertices;
	std::vector<PolygonMesh::Face> faces;
};

	}
}