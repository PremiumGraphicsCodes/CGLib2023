#pragma once

#include "Vector3d.h"
#include "ISurface3d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Rectangle3d : public ISurface3d<T>
{
public:
	Rectangle3d();

	Rectangle3d(const Vector3d<T>& origin, const Vector3d<T>& uvec, const Vector3d<T>& vvec);

	Vector3d<T> getPosition(const T u, const T v) const override;

	Vector3d<T> getNormal() const;

private:
	Vector3d<T> origin;
	Vector3d<T> uvec;
	Vector3d<T> vvec;
};

using Rectangle3df = Rectangle3d<float>;
using Rectangle3dd = Rectangle3d<double>;

	}
}