#pragma once

#include "glm.h"

namespace Crystal {
	namespace Math {

template<typename T>
using Vector3d = glm::vec<3, T>;

using Vector3df = Vector3d<float>;
using Vector3dd = Vector3d<double>;

template<typename T>
static T getDistanceSquared(const Vector3d<T>& lhs, const Vector3d<T>& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

	}
}