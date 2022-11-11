#pragma once

#include "CGLib/Math/Vector3d.h"
#include <vector>

namespace Crystal {
	namespace IO {

struct PCDFile
{
	struct Header
	{
		int width = 0;
		int points = 0;
		bool isBinary = false;
	};
	struct Data
	{
		std::vector<Math::Vector3df> positions;
	};
	Header header;
	Data data;
};

	}
}