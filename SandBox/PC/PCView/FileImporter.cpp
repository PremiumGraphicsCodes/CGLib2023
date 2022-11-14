#include "FileImporter.h"

using namespace Crystal::PC;

bool FileImporter::import(const std::filesystem::path& path)
{
	const auto ext = path.extension();
	if (ext == ".ply") {
		return importPLY(path);
	}
	else if (ext == ".pcd") {
		return importPCD(path);
	}
	else if (ext == ".txt") {
		return importTXT(path);
	}
	return false;
}

bool FileImporter::importPCD(const std::filesystem::path& path)
{
	return false;
}

bool FileImporter::importPLY(const std::filesystem::path& path)
{
	return false;
}

bool FileImporter::importTXT(const std::filesystem::path& path)
{
	return false;
}
