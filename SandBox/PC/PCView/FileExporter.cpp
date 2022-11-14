#include "FileExporter.h"

using namespace Crystal::PC;

void FileExporter::add(const std::unique_ptr<PointCloud>& pointCloud)
{
	const auto& points = pointCloud->getPoints();
	for (auto& p : points) {
		positions.push_back(p->getPosition());
		colors.push_back(p->getColor());
	}
}

bool FileExporter::export_(const std::filesystem::path& path)
{
	const auto ext = path.extension();
	if (ext == ".ply") {
		return exportPLY(path);
	}
	else if (ext == ".pcd") {
		return exportPCD(path);
	}
	else if (ext == ".txt") {
		return exportTXT(path);
	}
	return false;
}

bool FileExporter::exportPCD(const std::filesystem::path& path)
{
	return false;
}

bool FileExporter::exportPLY(const std::filesystem::path& path)
{
	return false;
}

bool FileExporter::exportTXT(const std::filesystem::path& path)
{
	return false;
}
