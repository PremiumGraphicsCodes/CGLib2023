#pragma once

#include "Vector3d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Line3d
{
public:
	Line3d();

	Line3d(const Math::Vector3d<T>& start, const Math::Vector3d<T>& end);

	Math::Vector3d<T> getStart() const { return start; }

	Math::Vector3d<T> getEnd() const { return end; }

	Math::Vector3d<T> getDirection() const { return end - start; }

private:
	Math::Vector3d<T> start;
	Math::Vector3d<T> end;
};

using Line3df = Line3d<float>;
using Line3dd = Line3d<double>;
	}
}