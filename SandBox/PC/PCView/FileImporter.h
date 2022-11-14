#pragma once

#include <filesystem>
#include "PointCloudScene.h"
#include "CGLib/Graphics/ColorRGBA.h"

namespace Crystal {
	namespace PC {

class FileImporter
{
public:
	bool import(const std::filesystem::path& path);

	std::unique_ptr<PointCloud> getPointCloud() { return std::move(pointCloud); }

private:
	bool importPCD(const std::filesystem::path& path);

	bool importPLY(const std::filesystem::path& path);

	bool importTXT(const std::filesystem::path& path);

	std::unique_ptr<PointCloud> pointCloud;
};

	}
}