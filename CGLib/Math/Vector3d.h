#pragma once

#include "glm.h"

namespace Crystal {
	namespace Math {

template<typename T>
using Vector3d = glm::vec<3, T>;

using Vector3df = Vector3d<float>;
using Vector3dd = Vector3d<double>;

	}
}