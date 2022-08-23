#pragma once

#include "glm.h"

namespace Crystal {
	namespace Math {

template<typename T>
using Vector2d = glm::vec<2, T>;

using Vector2df = Vector2d<float>;
using Vector2dd = Vector2d<double>;

	}
}