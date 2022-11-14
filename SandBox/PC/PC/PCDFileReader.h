#pragma once

#include <string>
#include <filesystem>

#include "PCDFile.h"

namespace Crystal {
	namespace PC {

class PCDFileReader
{
public:
	bool isBinary(std::istream& stream);

	bool isBinary(const std::filesystem::path& filepath);

	bool readAscii(std::istream& stream);

	bool read(const std::filesystem::path& filename);

	bool readBinary(std::istream& stream);

	PCDFile getPCD() const { return pcd; }

private:
	PCDFile::Header readHeader(std::istream& stream);

	PCDFile::Data readDataAscii(std::istream& stream);

	PCDFile::Data readDataBinary(std::istream& stream, const int howMany);

private:
	bool isOk;
	PCDFile pcd;
};

	}
}