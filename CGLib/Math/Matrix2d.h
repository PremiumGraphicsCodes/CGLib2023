#pragma once

#include "glm.h"

namespace Crystal {
	namespace Math {

template<typename T>
using Matrix2d = glm::mat<2, 2, T>;

using Matrix2df = Matrix2d<float>;
using Matrix2dd = Matrix2d<double>;

	}
}