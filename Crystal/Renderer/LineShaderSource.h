#pragma once

#include <string>

namespace Crystal {
	namespace Renderer {

class LineShaderSource
{
public:
	static std::string getVertexShaderSource();

	static std::string getFragmentShaderSource();
};

	}
}