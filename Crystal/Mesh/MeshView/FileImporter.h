#pragma once

#include <filesystem>
#include "PolygonMeshScene.h"

namespace Crystal {
	namespace Mesh {

class FileImporter
{
public:
	bool import(const std::filesystem::path& path);

	std::unique_ptr<PolygonMesh> getMesh() { return std::move(mesh); }

private:
	bool importSTL(const std::filesystem::path& path);

	bool importOBJ(const std::filesystem::path& path);

	std::unique_ptr<PolygonMesh> mesh;
};

	}
}