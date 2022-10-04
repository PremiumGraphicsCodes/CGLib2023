#include "DistanceCalculator.h"

#include "CGLib/Math/Ray3d.h"
#include "CGLib/Math/Sphere3d.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

template<typename T>
T DistanceCalculator<T>::calculate(const Math::Ray3d<T>& ray, const Math::Sphere3d<T>& sphere)
{
	const auto& direction = ray.getDirection();
	const auto& diff = sphere.getCenter() - ray.getOrigin();
	const auto t0 = glm::dot(diff, direction);
	const auto distanceSquared = glm::dot(diff, diff) - t0 * t0;
	const auto sphereRadiusSquared = sphere.getRadius() * sphere.getRadius();
	const auto t1 = std::sqrt(sphereRadiusSquared - distanceSquared);
	const auto intersectionDistance = t0 > t1 ? t0 - t1 : t0 + t1;
	return intersectionDistance;
}


template class DistanceCalculator<float>;
template class DistanceCalculator<double>;