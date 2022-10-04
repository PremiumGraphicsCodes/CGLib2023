#include "Cylinder3d.h"
#include "pi.h"

using namespace Crystal::Math;

template<typename T>
Cylinder3d<T>::Cylinder3d() :
	Cylinder3d(Vector3d<T>(0,0,0), Vector3d<T>(1,0,0), Vector3d<T>(0,1,0), Vector3d<T>(0,0,1))
{}

template<typename T>
Cylinder3d<T>::Cylinder3d(const Vector3d<T>& bottom, const Vector3d<T>& uvec, const Vector3d<T>& vvec, const Vector3d<T>& wvec) :
	bottom(bottom),
	uvec(uvec),
	vvec(vvec),
	wvec(wvec)
{}

template<typename T>
Vector3d<T> Cylinder3d<T>::getPosition(const T u, const T v) const
{
	const auto angle = T(2) * u * T(PI);

	const auto uu = std::cos(angle) * uvec;
	const auto vv = std::sin(angle) * vvec;
	const auto ww = v * wvec;
	return bottom + uu + vv + ww;
}

template class Cylinder3d<float>;
template class Cylinder3d<double>;