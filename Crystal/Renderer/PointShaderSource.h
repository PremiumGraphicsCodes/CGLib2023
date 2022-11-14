#pragma once

#include <string>

namespace Crystal {
	namespace Renderer {

class PointShaderSource
{
public:
	static std::string getVertexShaderSource();

	static std::string getFragmentShaderSource();

};
	}
}