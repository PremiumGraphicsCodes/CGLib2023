#pragma once

#include "../Math/glm.h"

namespace Crystal {
	namespace Graphics {

template<typename T>
using ColorRGBA = glm::vec<4, T>;

using ColorRGBAf = ColorRGBA<float>;
using ColorRGBAuc = ColorRGBA<glm::u8>;

	}
}