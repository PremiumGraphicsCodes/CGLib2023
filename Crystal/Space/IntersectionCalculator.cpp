#include "IntersectionCalculator.h"

#include "DistanceCalculator.h"

#include "CGLib/Math/Ray3d.h"
#include "CGLib/Math/Sphere3d.h"
#include "CGLib/Math/Plane3d.h"
#include "CGLib/Math/Triangle3d.h"
#include "CGLib/Math/Box3d.h"

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
	const auto p = DistanceCalculator<T>::calculate(ray, sphere, tolerance);
	if (p.empty()) {
		return false;
	}
	const auto intersectionDistance = p[0];
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
	const auto p = DistanceCalculator<T>::calculate(ray, triangle, tolerance);
	if (p.empty()) {
		return false;
	}

	intersections.push_back(ray.getPosition(p[0]));
	return true;
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

// ref https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
template<typename T>
bool IntersectionCalculator<T>::calculateIntersection(const Ray3d<T>& ray, const Box3d<T>& box, const T tolerance)
{
	// tmin, tmax -> parameter
	const auto origin = ray.getOrigin();
	const auto dir = ray.getDirection();

	const auto min = box.getMin();
	const auto max = box.getMax();
	auto tmin = (min.x - origin.x) / dir.x;
	auto tmax = (max.x - origin.x) / dir.x;

	if (tmin > tmax) std::swap(tmin, tmax);

	auto tymin = (min.y - origin.y) / dir.y;
	auto tymax = (max.y - origin.y) / dir.y;

	if (tymin > tymax) std::swap(tymin, tymax);

	if ((tmin > tymax) || (tymin > tmax))
		return false;

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	auto tzmin = (min.z - origin.z) / dir.z;
	auto tzmax = (max.z - origin.z) / dir.z;

	if (tzmin > tzmax) std::swap(tzmin, tzmax);

	if ((tmin > tzmax) || (tzmin > tmax))
		return false;

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;

	intersections.push_back(ray.getPosition(tmin));
	intersections.push_back(ray.getPosition(tmax));
	return true;
}

template class IntersectionCalculator<float>;
template class IntersectionCalculator<double>;