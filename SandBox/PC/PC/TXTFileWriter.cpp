#include "TXTFileWriter.h"

#include <fstream>

using namespace Crystal::Math;
using namespace Crystal::PC;

void TXTFileWriter::add(const Vector3df& position)
{
	positions.emplace_back(position);
}

bool TXTFileWriter::write(const std::filesystem::path& filePath)
{
	std::ofstream stream(filePath);
	if (!stream.is_open()) {
		return false;
	}

	for (const auto& p : positions) {
		stream << p.x << " " << p.y << " " << p.z << std::endl;
	}

	stream.close();
	return true;
}