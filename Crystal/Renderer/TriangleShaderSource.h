#pragma once

#include <string>

namespace Crystal {
	namespace Renderer {

class TriangleShaderSource
{
public:
	static std::string getVertexShaderSource();

	static std::string getFragmentShaderSource();
};

	}
}