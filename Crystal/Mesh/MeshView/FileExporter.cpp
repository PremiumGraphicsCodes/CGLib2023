#include "FileExporter.h"

using namespace Crystal::Mesh;

void FileExporter::add(const std::unique_ptr<PolygonMesh>& mesh)
{
	/*
	const auto& points = pointCloud->getPoints();
	for (auto& p : points) {
		positions.push_back(p->getPosition());
		colors.push_back(p->getColor());
	}
	*/
}

bool FileExporter::export_(const std::filesystem::path& path)
{
	const auto ext = path.extension();
	if (ext == ".obj") {
		return exportOBJ(path);
	}
	else if (ext == ".stl") {
		return exportSTL(path);
	}
	return false;
}

bool FileExporter::exportOBJ(const std::filesystem::path& path)
{
	return false;
}

bool FileExporter::exportSTL(const std::filesystem::path& path)
{
	return false;
}