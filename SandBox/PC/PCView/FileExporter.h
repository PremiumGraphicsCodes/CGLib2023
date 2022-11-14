#pragma once

#include <filesystem>
#include "PointCloudScene.h"

namespace Crystal {
	namespace PC {

class FileExporter
{
public:
	void add(const std::unique_ptr<PointCloud>& pointCloud);

	bool export_(const std::filesystem::path& path);

private:
	bool exportPCD(const std::filesystem::path& path);

	bool exportPLY(const std::filesystem::path& path);

	bool exportTXT(const std::filesystem::path& path);

	std::vector<Math::Vector3df> positions;
	std::vector<Graphics::ColorRGBAf> colors;
};

	}
}