#pragma once

#include <filesystem>

namespace Crystal {
	namespace PC {

class FileImporter
{
public:
	bool import(const std::filesystem::path& path);

private:
	bool importPCD(const std::filesystem::path& path);

	bool importPLY(const std::filesystem::path& path);

	bool importTXT(const std::filesystem::path& path);
};

	}
}