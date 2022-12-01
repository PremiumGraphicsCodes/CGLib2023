#pragma once

#include <string>

namespace Crystal {
	namespace Renderer {

		class TexShaderSource
		{
		public:
			static std::string getVertexShaderSource();

			static std::string getFragmentShaderSource();
		};

	}
}