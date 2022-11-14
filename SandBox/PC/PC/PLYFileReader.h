#pragma once

#include <string>
#include <filesystem>

#include "CGLib/Math/Vector3d.h"
#include "PLYFile.h"

namespace Crystal {
	namespace PC {

class PLYFileReader
{
public:
	bool read(const std::filesystem::path& filename);

	bool read(std::istream& stream);

	PLYFile getPLY() const { return ply; }

private:
	bool readAsciiData(std::istream& stream, const unsigned int count);

	bool readBinaryData(std::istream& stream, const unsigned int count);

private:
	PLYFile ply;
};

	}
}