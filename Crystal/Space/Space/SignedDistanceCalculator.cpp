#include "SignedDistanceCalculator.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

template<typename T>
T SignedDistanceCalculator<T>::calculate(const Vector3d<T>& position, const Sphere3d<T>& sphere)
{
	return 0;
}


template class SignedDistanceCalculator<float>;
template class SignedDistanceCalculator<double>;