#include "IntersectionCalculator.h"

#include "CGLib/Math/Ray3d.h"
#include "CGLib/Math/Sphere3d.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

template<typename T>
bool IntersectionCalculator<T>::calculateIntersection(const Ray3d<T>& ray, const Sphere3d<T>& sphere, const T tolerance)
{
	const auto& direction = ray.getDirection();
	const auto& diff = sphere.getCenter() - ray.getOrigin();
	const auto t0 = glm::dot(diff, direction);
	const auto distanceSquared = glm::dot(diff, diff) - t0 * t0;
	const auto sphereRadiusSquared = sphere.getRadius() * sphere.getRadius();
	if (distanceSquared > sphereRadiusSquared)
	{
		return false;
	}
	const auto t1 = std::sqrt(sphereRadiusSquared - distanceSquared);
	const auto intersectionDistance = t0 > t1 + tolerance ? t0 - t1 : t0 + t1;
	if (intersectionDistance > tolerance) {
		const auto& i = ray.getPosition(intersectionDistance);
		//const auto& normal = glm::normalize(i - sphere.getCenter());
		intersections.push_back(i);
		return true;
	}
	return false;
}

template class IntersectionCalculator<float>;
template class IntersectionCalculator<double>;