#include "IntersectionCalculator.h"

#include "CGLib/Math/Ray3d.h"
#include "CGLib/Math/Sphere3d.h"
#include "CGLib/Math/Plane3d.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

namespace {
	/*
bool Triangle3d::isInside(const Vector3dd& p) const
{
	const auto& n = getNormal();

	const auto a = vertices[0] - p;
	const auto b = vertices[1] - p;
	const auto c = vertices[2] - p;

	const auto d = vertices[1] - vertices[0];
	const auto e = vertices[2] - vertices[1];
	const auto f = vertices[0] - vertices[2];

	const auto& v1 = glm::cross(a, d);
	if (glm::dot(v1, n) < 0.0) {
		return false;
	}
	const auto& v2 = glm::cross(b, e);
	if (glm::dot(v2, n) < 0.0) {
		return false;
	}
	const auto& v3 = glm::cross(c, f);
	if (glm::dot(v3, n) < 0.0) {
		return false;
	}
	return true;
}
*/

}

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

template<typename T>
bool IntersectionCalculator<T>::calculateIntersection(const Ray3d<T>& ray, const Plane3d<T>& plane, const T tolerance)
{
	const auto distance = plane.getDistance(ray.getOrigin());

	if (distance > -tolerance)
	{
		const auto i = ray.getPosition(distance);
		intersections.push_back(i);
		return true;
	}
	return false;
}

template<typename T>
bool IntersectionCalculator<T>::calculateIntersection(const Ray3d<T>& ray, const Triangle3d<T>& triangle, const T tolerance)
{
	assert(false);
	return false;
}


template<typename T>
bool IntersectionCalculator<T>::calculateIntersection(const Ray3d<T>& ray, const Rectancle3d<T>& quad, const T tolerance)
{
	assert(false);
	/*
	const auto& plane = quad.toPlane();

	IntersectionCalculator innerAlgo;
	if (!innerAlgo.calculateIntersection(ray, plane, tolerance)) {
		return false;
	}

	auto s = innerAlgo.getIntersections()[0].position;
	if (quad.isInside(s)) {
		Intersection intersection;
		intersection.position = s;
		intersection.normal = quad.getNormal();
		intersections.push_back(intersection);
		return true;
	}
	*/
	return false;
}


template class IntersectionCalculator<float>;
template class IntersectionCalculator<double>;