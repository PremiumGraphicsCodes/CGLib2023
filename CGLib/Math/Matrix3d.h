#pragma once

#include "glm.h"

namespace Crystal {
	namespace Math {

template<typename T>
using Matrix3d = glm::mat<3, 3, T>;

using Matrix3df = Matrix3d<float>;
using Matrix3dd = Matrix3d<double>;

	}
}