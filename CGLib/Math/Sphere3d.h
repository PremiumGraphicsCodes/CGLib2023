#pragma once

#include "Vector3d.h"
#include "ISurface3d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Box3d;

template<typename T>
class Sphere3d : public ISurface3d<T>
{
public:
	Sphere3d();

	Sphere3d(const Vector3d<T>& center, const T radius);

	Vector3d<T> getPosition(const T u, const T v) const override;

	Vector3d<T> getPosition(const T u, const T v, const T w) const; //const override;

	Vector3d<T> getNormal(const T u, const T v) const;// const override;

	Vector3d<T> getCenter() const { return center; }

	T getRadius() const { return radius; }

	Box3d<T> getBoundingBox() const;

private:
	Vector3d<T> center;
	T radius;
};

using Sphere3df = Sphere3d<float>;
using Sphere3dd = Sphere3d<double>;

	}
}