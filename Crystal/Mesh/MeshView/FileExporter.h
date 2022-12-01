#pragma once

#include <filesystem>
#include "../Mesh/PolygonMesh.h"

namespace Crystal {
	namespace Mesh {

class FileExporter
{
public:
	void add(const PolygonMesh& mesh);

	bool export_(const std::filesystem::path& path);

private:
	bool exportOBJ(const std::filesystem::path& path);

	bool exportSTL(const std::filesystem::path& path);

	//bool exportTXT(const std::filesystem::path& path);

	std::vector<PolygonMesh::Face> faces;
	std::vector<PolygonMesh::Vertex> vertices;
	std::vector<Math::Vector3df> positions;
	std::vector<Math::Vector3df> normals;
	std::vector<Math::Vector2df> texCoords;
};

	}
}