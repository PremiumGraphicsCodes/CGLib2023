#pragma once

#include <string>

namespace Crystal {
	namespace Renderer {

class SkyBoxShaderSource
{
public:
	static std::string getVertexShaderSource();

	static std::string getFragmentShaderSource();
};

	}
}