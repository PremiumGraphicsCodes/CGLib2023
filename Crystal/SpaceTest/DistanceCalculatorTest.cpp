#include "gtest/gtest.h"
#include "../Space/DistanceCalculator.h"

#include "CGLib/Math/Ray3d.h"
#include "CGLib/Math/Sphere3d.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

TEST(DistanceCalculatorTest, TestRayAndSphere)
{
	DistanceCalculator<float> c;
	Ray3df ray(Vector3df(0, 0, 0), Vector3df(1, 0, 0));
	Sphere3df sphere(Vector3df(10, 0, 0), 1.0f);
	const auto d = c.calculate(ray, sphere, 1.0e-9f);
	EXPECT_EQ(d.size(), 1);
	EXPECT_FLOAT_EQ(d[0], 9.0);
}