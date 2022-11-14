#pragma once

#include <filesystem>
#include "CGLib/Math/Vector3d.h"

namespace Crystal {
	namespace PC {

class TXTFileWriter
{
public:
	void add(const Math::Vector3df& position);

	bool write(const std::filesystem::path& filePath);

private:
	std::vector<Math::Vector3df> positions;
};

	}
}