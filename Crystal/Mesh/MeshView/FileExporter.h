#pragma once

#include <filesystem>
#include "PolygonMeshScene.h"

namespace Crystal {
	namespace Mesh {

class FileExporter
{
public:
	void add(const std::unique_ptr<PolygonMesh>& mesh);

	bool export_(const std::filesystem::path& path);

private:
	bool exportOBJ(const std::filesystem::path& path);

	bool exportSTL(const std::filesystem::path& path);

	//bool exportTXT(const std::filesystem::path& path);

	std::vector<Math::Vector3df> positions;
	std::vector<Math::Vector3df> normals;
	std::vector<Math::Vector2df> texCoords;
};

	}
}