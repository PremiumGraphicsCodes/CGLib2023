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
		template<typename T>
		class Rectancle3d;
		template<typename T>
		class Box3d;
	}
	namespace Space {

template<typename T>
class SignedDistanceCalculator
{
public:
	static T calculate(const Math::Vector3d<T>& position, const Math::Sphere3d<T>& sphere);

	static T calculate(const Math::Vector3d<T>& position, const Math::Plane3d<T>& plane);

	//static T calculate(const Math::Vector3d<T>& position, const Math::Box3d<T>& box);
};
	}
}