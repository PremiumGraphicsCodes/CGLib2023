#include "gtest/gtest.h"
#include "../Space/IntersectionCalculator.h"

#include "CGLib/Math/Ray3d.h"
#include "CGLib/Math/Sphere3d.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

TEST(IntersectionCalculatorTest, TestRayAndSphere)
{
	IntersectionCalculator<float> c;
	Ray3df ray(Vector3df(0,0,0), Vector3df(1,0,0));
	Sphere3df sphere(Vector3df(10, 0, 0), 1.0f);
	const auto found = c.calculateIntersection(ray, sphere, 1.0e-9f);
	const auto actual = c.getIntersections()[0];
	Vector3df expected(9, 0, 0);
	EXPECT_TRUE(areSame(expected, actual, 1.0e-9f));
}