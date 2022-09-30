#pragma once

#include "CGLib/Math/Vector3d.h"
#include <vector>

namespace Crystal {
	namespace Math {
		template<typename T>
		class Line3d;
		template<typename T>
		class Sphere3d;
		template<typename T>
		class Ray3d;
		template<typename T>
		class Plane3d;
		template<typename T>
		class Triangle3d;
		//class Quad3d;
		template<typename T>
		class Box3d;
	}
	namespace Space {

template<typename T>
class IntersectionCalculator
{
public:
	bool calculateIntersection(const Math::Ray3d<T>& ray, const Math::Sphere3d<T>& sphere, const T tolerance);

	/*
	bool calculateIntersection(const Math::Ray3d<T>& ray, const Math::Plane3d& plane, const T tolerance);

	bool calculateIntersection(const Math::Ray3df& ray, const Math::Triangle3d& triangle, const double tolerance);

	bool calculateIntersection(const Math::Ray3df& ray, const Math::Quad3d& quad, const double tolerance);

	bool calculateIntersection(const Math::Ray3df& ray, const Math::Box3df& box, const double tolerance);

	bool calculateIntersection(const Math::Line3df& line, const Math::Plane3d& plane, const double tolerance);

	bool calculateIntersection(const Math::Line3df& line, const Math::Sphere3df& sphere, const double tolerance);

	bool calculateIntersection(const Math::Line3df& line, const Math::Triangle3d& triangle, const double tolerance);

	bool calculateIntersection(const Math::Line3df& line, const Math::Quad3d& quad, const double tolerance);

	bool calculateIntersection(const Math::Triangle3d& lhs, const Math::Triangle3d& rhs, const double tolerance);
	*/

	std::vector<Math::Vector3d<T>> getIntersections() const { return intersections; }

private:
	std::vector<Math::Vector3d<T>> intersections;
};
	}
}