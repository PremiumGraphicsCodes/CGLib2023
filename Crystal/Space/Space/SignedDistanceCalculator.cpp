#include "SignedDistanceCalculator.h"

#include "CGLib/Math/Sphere3d.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

template<typename T>
T SignedDistanceCalculator<T>::calculate(const Vector3d<T>& position, const Sphere3d<T>& sphere)
{
	const auto d = ::getDistance(position, sphere.getCenter());
	const auto r = sphere.getRadius();
	return d - r;
}


template class SignedDistanceCalculator<float>;
template class SignedDistanceCalculator<double>;